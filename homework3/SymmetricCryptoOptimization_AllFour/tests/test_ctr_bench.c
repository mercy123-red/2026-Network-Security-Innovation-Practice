#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aes_ctr.h"

typedef void (*ctr_fn)(const aes128_ctx *, const uint8_t[16],
                       const uint8_t *, uint8_t *, size_t);

static double now_seconds(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

static int bytes_equal(const uint8_t *a, const uint8_t *b, size_t n) {
    unsigned diff = 0;
    for (size_t i = 0; i < n; ++i) {
        diff |= (unsigned)(a[i] ^ b[i]);
    }
    return diff == 0U;
}

static void print_hex(const uint8_t *p, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%02x", p[i]);
    }
}

static int check_ctr(const char *name, ctr_fn fn, const aes128_ctx *ctx,
                     const uint8_t ctr[16], const uint8_t *pt,
                     const uint8_t *expected, size_t len) {
    uint8_t *out = malloc(len == 0U ? 1U : len);
    uint8_t *recovered = malloc(len == 0U ? 1U : len);
    if (out == NULL || recovered == NULL) {
        free(out);
        free(recovered);
        fprintf(stderr, "allocation failure\n");
        return 0;
    }

    fn(ctx, ctr, pt, out, len);
    const int known_answer_ok = bytes_equal(out, expected, len);
    fn(ctx, ctr, out, recovered, len);
    const int round_trip_ok = bytes_equal(recovered, pt, len);

    /* Verify in-place operation too. */
    memcpy(recovered, pt, len);
    fn(ctx, ctr, recovered, recovered, len);
    const int inplace_ok = bytes_equal(recovered, expected, len);

    const int ok = known_answer_ok && round_trip_ok && inplace_ok;
    printf("[%-22s] %s", name, ok ? "PASS" : "FAIL");
    if (!known_answer_ok) {
        printf("  got=");
        print_hex(out, len);
    }
    putchar('\n');

    free(out);
    free(recovered);
    return ok;
}

static double bench_ctr(const char *name, ctr_fn fn,
                        const aes128_ctx *ctx, const uint8_t ctr[16],
                        uint8_t *input, uint8_t *output, size_t bytes,
                        FILE *csv) {
    const double start = now_seconds();
    fn(ctx, ctr, input, output, bytes);
    const double elapsed = now_seconds() - start;
    const double mib_s = ((double)bytes / (1024.0 * 1024.0)) / elapsed;

    printf("%-24s %10.2f MiB/s  checksum=%02x\n",
           name, mib_s, output[bytes - 1U]);
    if (csv != NULL) {
        fprintf(csv, "%s,%.6f\n", name, mib_s);
    }
    return mib_s;
}

int main(int argc, char **argv) {
    size_t bench_mib = 64U;
    if (argc == 2) {
        char *end = NULL;
        errno = 0;
        const unsigned long parsed = strtoul(argv[1], &end, 10);
        if (errno != 0 || end == argv[1] || *end != '\0' || parsed == 0UL) {
            fprintf(stderr, "usage: %s [MiB]\n", argv[0]);
            return EXIT_FAILURE;
        }
        bench_mib = (size_t)parsed;
    }

    /* NIST SP 800-38A, Appendix F.5.1, AES-128 CTR. */
    const uint8_t key[16] = {
        0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
        0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c
    };
    const uint8_t initial_counter[16] = {
        0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,
        0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff
    };
    const uint8_t plaintext[64] = {
        0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,
        0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51,
        0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef,
        0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10
    };
    const uint8_t ciphertext[64] = {
        0x87,0x4d,0x61,0x91,0xb6,0x20,0xe3,0x26,0x1b,0xef,0x68,0x64,0x99,0x0d,0xb6,0xce,
        0x98,0x06,0xf6,0x6b,0x79,0x70,0xfd,0xff,0x86,0x17,0x18,0x7b,0xb9,0xff,0xfd,0xff,
        0x5a,0xe4,0xdf,0x3e,0xdb,0xd5,0xd3,0x5e,0x5b,0x4f,0x09,0x02,0x0d,0xb0,0x3e,0xab,
        0x1e,0x03,0x1d,0xda,0x2f,0xbe,0x03,0xd1,0x79,0x21,0x70,0xa0,0xf3,0x00,0x9c,0xee
    };

    aes128_ctx ctx;
    if (aes128_init(&ctx, key) != 0) {
        fprintf(stderr, "aes128_init failed\n");
        return EXIT_FAILURE;
    }

    puts("AES-128 CTR known-answer tests (NIST SP 800-38A F.5.1)");
    int ok = 1;
    ok &= check_ctr("CTR basic", aes128_ctr_crypt_basic, &ctx,
                    initial_counter, plaintext, ciphertext, sizeof(plaintext));
    ok &= check_ctr("CTR T-table", aes128_ctr_crypt_ttable, &ctx,
                    initial_counter, plaintext, ciphertext, sizeof(plaintext));
    ok &= check_ctr("CTR shuffle", aes128_ctr_crypt_shuffle, &ctx,
                    initial_counter, plaintext, ciphertext, sizeof(plaintext));
    ok &= check_ctr("CTR AES-NI", aes128_ctr_crypt_aesni, &ctx,
                    initial_counter, plaintext, ciphertext, sizeof(plaintext));
    ok &= check_ctr("CTR VAES x8", aes128_ctr_crypt_vaes8, &ctx,
                    initial_counter, plaintext, ciphertext, sizeof(plaintext));

    /* Exercise partial final blocks and counter carry. */
    uint8_t carry_counter[16];
    uint8_t partial_plain[37];
    uint8_t serial_out[37], vaes_out[37], recovered[37];
    memset(carry_counter, 0xff, sizeof(carry_counter));
    carry_counter[0] = 0x7f;
    for (size_t i = 0; i < sizeof(partial_plain); ++i) {
        partial_plain[i] = (uint8_t)(3U * i + 1U);
    }
    aes128_ctr_crypt_aesni(&ctx, carry_counter, partial_plain,
                           serial_out, sizeof(serial_out));
    aes128_ctr_crypt_vaes8(&ctx, carry_counter, partial_plain,
                           vaes_out, sizeof(vaes_out));
    aes128_ctr_crypt_vaes8(&ctx, carry_counter, vaes_out,
                           recovered, sizeof(recovered));
    const int partial_ok = bytes_equal(serial_out, vaes_out, sizeof(vaes_out)) &&
                           bytes_equal(recovered, partial_plain, sizeof(recovered));
    printf("[%-22s] %s\n", "partial/carry test", partial_ok ? "PASS" : "FAIL");
    ok &= partial_ok;

    /* Force execution of the eight-block VAES loop and its tail path. */
    uint8_t long_plain[257], long_serial[257], long_vaes[257], long_recovered[257];
    for (size_t i = 0; i < sizeof(long_plain); ++i) {
        long_plain[i] = (uint8_t)(i * 29U + 0x5aU);
    }
    aes128_ctr_crypt_aesni(&ctx, initial_counter, long_plain,
                           long_serial, sizeof(long_serial));
    aes128_ctr_crypt_vaes8(&ctx, initial_counter, long_plain,
                           long_vaes, sizeof(long_vaes));
    aes128_ctr_crypt_vaes8(&ctx, initial_counter, long_vaes,
                           long_recovered, sizeof(long_recovered));
    const int multiblock_ok =
        bytes_equal(long_serial, long_vaes, sizeof(long_vaes)) &&
        bytes_equal(long_recovered, long_plain, sizeof(long_recovered));
    printf("[%-22s] %s\n", "VAES loop+tail test",
           multiblock_ok ? "PASS" : "FAIL");
    ok &= multiblock_ok;

    if (!ok) {
        fputs("At least one CTR correctness test failed; benchmark aborted.\n", stderr);
        return EXIT_FAILURE;
    }

    const size_t bytes = bench_mib * 1024U * 1024U;
    uint8_t *input = aligned_alloc(32, (bytes + 31U) & ~(size_t)31U);
    uint8_t *output = aligned_alloc(32, (bytes + 31U) & ~(size_t)31U);
    if (input == NULL || output == NULL) {
        free(input);
        free(output);
        fputs("benchmark allocation failed\n", stderr);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < bytes; ++i) {
        input[i] = (uint8_t)(i * 131U + 17U);
    }

    if (system("mkdir -p results") != 0) {
        fputs("warning: could not create results directory\n", stderr);
    }
    FILE *csv = fopen("results/ctr_benchmark.csv", "w");
    if (csv != NULL) {
        fputs("implementation,mib_per_second\n", csv);
    }

    printf("\nCTR benchmark size: %zu MiB per implementation\n", bench_mib);
    bench_ctr("AES-CTR basic", aes128_ctr_crypt_basic, &ctx,
              initial_counter, input, output, bytes, csv);
    bench_ctr("AES-CTR T-table", aes128_ctr_crypt_ttable, &ctx,
              initial_counter, input, output, bytes, csv);
    bench_ctr("AES-CTR shuffle", aes128_ctr_crypt_shuffle, &ctx,
              initial_counter, input, output, bytes, csv);
    bench_ctr("AES-CTR AES-NI", aes128_ctr_crypt_aesni, &ctx,
              initial_counter, input, output, bytes, csv);
    bench_ctr("AES-CTR VAES x8", aes128_ctr_crypt_vaes8, &ctx,
              initial_counter, input, output, bytes, csv);

    if (csv != NULL) {
        fclose(csv);
        puts("\nCSV written to results/ctr_benchmark.csv");
    }
    free(input);
    free(output);
    return EXIT_SUCCESS;
}
