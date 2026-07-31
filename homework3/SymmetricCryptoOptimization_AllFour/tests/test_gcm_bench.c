#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aes_gcm.h"

typedef int (*gcm_encrypt_fn)(const aes128_gcm_ctx *,
                              const uint8_t *, size_t,
                              const uint8_t *, size_t,
                              const uint8_t *, uint8_t *, size_t,
                              uint8_t[16]);
typedef int (*gcm_decrypt_fn)(const aes128_gcm_ctx *,
                              const uint8_t *, size_t,
                              const uint8_t *, size_t,
                              const uint8_t *, uint8_t *, size_t,
                              const uint8_t[16]);

static double now_seconds(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

static int bytes_equal(const uint8_t *a, const uint8_t *b, size_t n) {
    uint8_t diff = 0;
    for (size_t i = 0; i < n; ++i) {
        diff |= (uint8_t)(a[i] ^ b[i]);
    }
    return diff == 0U;
}

static void print_hex(const uint8_t *p, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%02x", p[i]);
    }
}

static int run_vector(const char *name,
                      gcm_encrypt_fn encrypt,
                      gcm_decrypt_fn decrypt,
                      const aes128_gcm_ctx *ctx,
                      const uint8_t *iv, size_t iv_len,
                      const uint8_t *aad, size_t aad_len,
                      const uint8_t *pt, size_t pt_len,
                      const uint8_t *expected_ct,
                      const uint8_t expected_tag[16]) {
    uint8_t *ct = calloc(pt_len == 0 ? 1 : pt_len, 1);
    uint8_t *recovered = calloc(pt_len == 0 ? 1 : pt_len, 1);
    uint8_t tag[16];
    if (ct == NULL || recovered == NULL) {
        fprintf(stderr, "allocation failed\n");
        free(ct);
        free(recovered);
        return 0;
    }

    int ok = encrypt(ctx, iv, iv_len, aad, aad_len,
                     pt, ct, pt_len, tag) == 0;
    ok &= bytes_equal(ct, expected_ct, pt_len);
    ok &= bytes_equal(tag, expected_tag, 16);
    ok &= decrypt(ctx, iv, iv_len, aad, aad_len,
                  ct, recovered, pt_len, tag) == 0;
    ok &= bytes_equal(recovered, pt, pt_len);

    printf("[%-28s] %s", name, ok ? "PASS" : "FAIL");
    if (!ok) {
        printf("\n  ciphertext=");
        print_hex(ct, pt_len);
        printf("\n  tag       =");
        print_hex(tag, 16);
    }
    putchar('\n');

    free(ct);
    free(recovered);
    return ok;
}

static int test_ghash_equivalence(void) {
    uint8_t h[16], data[79], a[16] = {0}, b[16] = {0};
    for (unsigned i = 0; i < 16; ++i) h[i] = (uint8_t)(0x31U*i + 7U);
    for (unsigned i = 0; i < sizeof(data); ++i) data[i] = (uint8_t)(0x9dU*i + 3U);
    aes_gcm_ghash_basic(h, data, sizeof(data), a);
    aes_gcm_ghash_pclmul(h, data, sizeof(data), b);
    const int ok = bytes_equal(a, b, 16);
    printf("[%-28s] %s\n", "GHASH basic vs PCLMUL", ok ? "PASS" : "FAIL");
    return ok;
}

static int test_tag_rejection(const aes128_gcm_ctx *ctx) {
    uint8_t iv[12] = {0};
    uint8_t pt[37], ct[37], out[37], tag[16];
    for (unsigned i = 0; i < sizeof(pt); ++i) pt[i] = (uint8_t)i;
    if (aes128_gcm_encrypt_aesni_pclmul(ctx, iv, sizeof(iv), NULL, 0,
                                       pt, ct, sizeof(pt), tag) != 0) {
        return 0;
    }
    tag[5] ^= 0x80;
    memset(out, 0xa5, sizeof(out));
    const int rc = aes128_gcm_decrypt_aesni_pclmul(
        ctx, iv, sizeof(iv), NULL, 0, ct, out, sizeof(out), tag);
    uint8_t zero[37] = {0};
    const int ok = rc == -2 && bytes_equal(out, zero, sizeof(out));
    printf("[%-28s] %s\n", "modified tag rejection", ok ? "PASS" : "FAIL");
    return ok;
}

static int test_general_iv_and_in_place(const aes128_gcm_ctx *ctx) {
    uint8_t iv[19], aad[23], plain[257], a[257], b[257], tag_a[16], tag_b[16];
    for (unsigned i = 0; i < sizeof(iv); ++i) iv[i] = (uint8_t)(i*7U + 1U);
    for (unsigned i = 0; i < sizeof(aad); ++i) aad[i] = (uint8_t)(i*11U + 2U);
    for (unsigned i = 0; i < sizeof(plain); ++i) plain[i] = (uint8_t)(i*13U + 9U);

    memcpy(a, plain, sizeof(a));
    memcpy(b, plain, sizeof(b));
    int ok = aes128_gcm_encrypt_basic(ctx, iv, sizeof(iv), aad, sizeof(aad),
                                      a, a, sizeof(a), tag_a) == 0;
    ok &= aes128_gcm_encrypt_vaes8_pclmul(ctx, iv, sizeof(iv), aad, sizeof(aad),
                                          b, b, sizeof(b), tag_b) == 0;
    ok &= bytes_equal(a, b, sizeof(a));
    ok &= bytes_equal(tag_a, tag_b, sizeof(tag_a));
    ok &= aes128_gcm_decrypt_vaes8_pclmul(ctx, iv, sizeof(iv), aad, sizeof(aad),
                                          b, b, sizeof(b), tag_b) == 0;
    ok &= bytes_equal(b, plain, sizeof(b));
    printf("[%-28s] %s\n", "general IV + in-place + tail", ok ? "PASS" : "FAIL");
    return ok;
}

static double bench_encrypt(const char *name, gcm_encrypt_fn fn,
                            const aes128_gcm_ctx *ctx,
                            const uint8_t *input, uint8_t *output,
                            size_t bytes, FILE *csv) {
    const uint8_t iv[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    const uint8_t aad[32] = {
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
        16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    };
    uint8_t tag[16];
    const double begin = now_seconds();
    const int rc = fn(ctx, iv, sizeof(iv), aad, sizeof(aad),
                      input, output, bytes, tag);
    const double elapsed = now_seconds() - begin;
    if (rc != 0) {
        fprintf(stderr, "%s failed\n", name);
        return 0.0;
    }
    const double mib_s = ((double)bytes / (1024.0*1024.0)) / elapsed;
    printf("%-30s %10.2f MiB/s  tag0=%02x\n", name, mib_s, tag[0]);
    if (csv != NULL) fprintf(csv, "%s,%.6f\n", name, mib_s);
    return mib_s;
}

int main(int argc, char **argv) {
    size_t bench_mib = 8;
    if (argc == 2) {
        char *end = NULL;
        errno = 0;
        const unsigned long parsed = strtoul(argv[1], &end, 10);
        if (errno != 0 || end == argv[1] || *end != '\0' || parsed == 0) {
            fprintf(stderr, "usage: %s [MiB]\n", argv[0]);
            return EXIT_FAILURE;
        }
        bench_mib = (size_t)parsed;
    }

    const uint8_t zero_key[16] = {0};
    const uint8_t zero_iv[12] = {0};
    const uint8_t zero_pt[16] = {0};
    const uint8_t empty_dummy[1] = {0};
    const uint8_t zero_ct[16] = {
        0x03,0x88,0xda,0xce,0x60,0xb6,0xa3,0x92,
        0xf3,0x28,0xc2,0xb9,0x71,0xb2,0xfe,0x78
    };
    const uint8_t zero_tag[16] = {
        0xab,0x6e,0x47,0xd4,0x2c,0xec,0x13,0xbd,
        0xf5,0x3a,0x67,0xb2,0x12,0x57,0xbd,0xdf
    };
    const uint8_t empty_tag[16] = {
        0x58,0xe2,0xfc,0xce,0xfa,0x7e,0x30,0x61,
        0x36,0x7f,0x1d,0x57,0xa4,0xe7,0x45,0x5a
    };

    const uint8_t key2[16] = {
        0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,
        0x6d,0x6a,0x8f,0x94,0x67,0x30,0x83,0x08
    };
    const uint8_t iv2[12] = {
        0xca,0xfe,0xba,0xbe,0xfa,0xce,0xdb,0xad,0xde,0xca,0xf8,0x88
    };
    const uint8_t aad2[20] = {
        0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xfe,0xed,
        0xfa,0xce,0xde,0xad,0xbe,0xef,0xab,0xad,0xda,0xd2
    };
    const uint8_t pt2[60] = {
        0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
        0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
        0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
        0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39
    };
    const uint8_t ct2[60] = {
        0x42,0x83,0x1e,0xc2,0x21,0x77,0x74,0x24,0x4b,0x72,0x21,0xb7,0x84,0xd0,0xd4,0x9c,
        0xe3,0xaa,0x21,0x2f,0x2c,0x02,0xa4,0xe0,0x35,0xc1,0x7e,0x23,0x29,0xac,0xa1,0x2e,
        0x21,0xd5,0x14,0xb2,0x54,0x66,0x93,0x1c,0x7d,0x8f,0x6a,0x5a,0xac,0x84,0xaa,0x05,
        0x1b,0xa3,0x0b,0x39,0x6a,0x0a,0xac,0x97,0x3d,0x58,0xe0,0x91
    };
    const uint8_t tag2[16] = {
        0x5b,0xc9,0x4f,0xbc,0x32,0x21,0xa5,0xdb,
        0x94,0xfa,0xe9,0x5a,0xe7,0x12,0x1a,0x47
    };

    aes128_gcm_ctx ctx0, ctx2;
    if (aes128_gcm_init(&ctx0, zero_key) != 0 ||
        aes128_gcm_init(&ctx2, key2) != 0) {
        fprintf(stderr, "GCM initialization failed\n");
        return EXIT_FAILURE;
    }

    puts("AES-128-GCM known-answer and robustness tests");
    int ok = 1;
    ok &= test_ghash_equivalence();
    ok &= run_vector("basic: empty plaintext", aes128_gcm_encrypt_basic,
                     aes128_gcm_decrypt_basic, &ctx0,
                     zero_iv, sizeof(zero_iv), NULL, 0,
                     empty_dummy, 0, empty_dummy, empty_tag);
    ok &= run_vector("basic: one zero block", aes128_gcm_encrypt_basic,
                     aes128_gcm_decrypt_basic, &ctx0,
                     zero_iv, sizeof(zero_iv), NULL, 0,
                     zero_pt, sizeof(zero_pt), zero_ct, zero_tag);
    ok &= run_vector("AESNI+PCLMUL: zero block",
                     aes128_gcm_encrypt_aesni_pclmul,
                     aes128_gcm_decrypt_aesni_pclmul, &ctx0,
                     zero_iv, sizeof(zero_iv), NULL, 0,
                     zero_pt, sizeof(zero_pt), zero_ct, zero_tag);
    ok &= run_vector("VAES8+PCLMUL: zero block",
                     aes128_gcm_encrypt_vaes8_pclmul,
                     aes128_gcm_decrypt_vaes8_pclmul, &ctx0,
                     zero_iv, sizeof(zero_iv), NULL, 0,
                     zero_pt, sizeof(zero_pt), zero_ct, zero_tag);
    ok &= run_vector("basic: AAD + partial block", aes128_gcm_encrypt_basic,
                     aes128_gcm_decrypt_basic, &ctx2,
                     iv2, sizeof(iv2), aad2, sizeof(aad2),
                     pt2, sizeof(pt2), ct2, tag2);
    ok &= run_vector("AESNI+PCLMUL: AAD+partial",
                     aes128_gcm_encrypt_aesni_pclmul,
                     aes128_gcm_decrypt_aesni_pclmul, &ctx2,
                     iv2, sizeof(iv2), aad2, sizeof(aad2),
                     pt2, sizeof(pt2), ct2, tag2);
    ok &= run_vector("VAES8+PCLMUL: AAD+partial",
                     aes128_gcm_encrypt_vaes8_pclmul,
                     aes128_gcm_decrypt_vaes8_pclmul, &ctx2,
                     iv2, sizeof(iv2), aad2, sizeof(aad2),
                     pt2, sizeof(pt2), ct2, tag2);
    ok &= test_tag_rejection(&ctx0);
    ok &= test_general_iv_and_in_place(&ctx2);

    if (!ok) {
        fprintf(stderr, "At least one GCM test failed; benchmark aborted.\n");
        return EXIT_FAILURE;
    }

    const size_t bytes = bench_mib * 1024U * 1024U;
    uint8_t *input = malloc(bytes);
    uint8_t *output = malloc(bytes);
    if (input == NULL || output == NULL) {
        fprintf(stderr, "benchmark allocation failed\n");
        free(input);
        free(output);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < bytes; ++i) input[i] = (uint8_t)(i*29U + 7U);

    if (system("mkdir -p results") != 0) {
        fprintf(stderr, "warning: could not create results directory\n");
    }
    FILE *csv = fopen("results/gcm_benchmark.csv", "w");
    if (csv != NULL) fputs("implementation,mib_per_second\n", csv);

    printf("\nGCM encryption benchmark: %zu MiB per implementation\n", bench_mib);
    bench_encrypt("AES-GCM basic", aes128_gcm_encrypt_basic,
                  &ctx2, input, output, bytes, csv);
    bench_encrypt("AESNI + PCLMULQDQ",
                  aes128_gcm_encrypt_aesni_pclmul,
                  &ctx2, input, output, bytes, csv);
    bench_encrypt("VAES x8 + PCLMULQDQ",
                  aes128_gcm_encrypt_vaes8_pclmul,
                  &ctx2, input, output, bytes, csv);

    if (csv != NULL) {
        fclose(csv);
        puts("CSV written to results/gcm_benchmark.csv");
    }
    free(input);
    free(output);
    return EXIT_SUCCESS;
}
