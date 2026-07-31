#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aes.h"

typedef void (*block_fn)(const aes128_ctx *, const uint8_t *, uint8_t *);

static double now_seconds(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

static int equal16(const uint8_t a[16], const uint8_t b[16]) {
    unsigned diff = 0;
    for (unsigned i = 0; i < 16; ++i) {
        diff |= (unsigned)(a[i] ^ b[i]);
    }
    return diff == 0;
}

static void print_hex(const uint8_t *p, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%02x", p[i]);
    }
}

static int check_block(const char *name, block_fn fn,
                       const aes128_ctx *ctx,
                       const uint8_t pt[16], const uint8_t expected[16]) {
    uint8_t out[16];
    fn(ctx, pt, out);
    const int ok = equal16(out, expected);
    printf("[%-20s] %s", name, ok ? "PASS" : "FAIL");
    if (!ok) {
        printf("  got=");
        print_hex(out, 16);
    }
    putchar('\n');
    return ok;
}

static double bench_block(const char *name, block_fn fn,
                          const aes128_ctx *ctx, size_t bytes,
                          FILE *csv) {
    const size_t blocks = bytes / 16;
    uint8_t in[16] = {0};
    uint8_t out[16] = {0};

    const double begin = now_seconds();
    for (size_t i = 0; i < blocks; ++i) {
        in[0] = (uint8_t)i;
        in[7] ^= out[3];
        fn(ctx, in, out);
    }
    const double elapsed = now_seconds() - begin;
    const double mib_s = ((double)bytes / (1024.0 * 1024.0)) / elapsed;

    printf("%-22s %10.2f MiB/s  checksum=%02x\n", name, mib_s, out[0]);
    if (csv != NULL) {
        fprintf(csv, "%s,%.6f\n", name, mib_s);
    }
    return mib_s;
}

static double bench_vaes(const aes128_ctx *ctx, size_t bytes, FILE *csv) {
    const size_t groups = bytes / 128;
    uint8_t in[128] = {0};
    uint8_t out[128] = {0};

    const double begin = now_seconds();
    for (size_t i = 0; i < groups; ++i) {
        in[0] = (uint8_t)i;
        in[63] ^= out[17];
        aes128_encrypt8_vaes(ctx, in, out);
    }
    const double elapsed = now_seconds() - begin;
    const double mib_s = ((double)(groups * 128) / (1024.0 * 1024.0)) / elapsed;

    printf("%-22s %10.2f MiB/s  checksum=%02x\n", "AES-128 VAES x8", mib_s, out[0]);
    if (csv != NULL) {
        fprintf(csv, "AES-128 VAES x8,%.6f\n", mib_s);
    }
    return mib_s;
}

int main(int argc, char **argv) {
    size_t bench_mib = 64;
    if (argc == 2) {
        char *end = NULL;
        errno = 0;
        unsigned long parsed = strtoul(argv[1], &end, 10);
        if (errno != 0 || end == argv[1] || *end != '\0' || parsed == 0) {
            fprintf(stderr, "usage: %s [MiB]\n", argv[0]);
            return EXIT_FAILURE;
        }
        bench_mib = (size_t)parsed;
    }

    const uint8_t key[16] = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
    };
    const uint8_t pt[16] = {
        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
        0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff
    };
    const uint8_t ct[16] = {
        0x69,0xc4,0xe0,0xd8,0x6a,0x7b,0x04,0x30,
        0xd8,0xcd,0xb7,0x80,0x70,0xb4,0xc5,0x5a
    };

    aes128_ctx ctx;
    if (aes128_init(&ctx, key) != 0) {
        fprintf(stderr, "aes128_init failed\n");
        return EXIT_FAILURE;
    }

    puts("AES-128 known-answer tests (FIPS-197 vector)");
    int ok = 1;
    ok &= check_block("basic encrypt", aes128_encrypt_basic, &ctx, pt, ct);
    ok &= check_block("T-table encrypt", aes128_encrypt_ttable, &ctx, pt, ct);
    ok &= check_block("shuffle encrypt", aes128_encrypt_shuffle, &ctx, pt, ct);
    ok &= check_block("AES-NI encrypt", aes128_encrypt_aesni, &ctx, pt, ct);
    ok &= check_block("basic decrypt", aes128_decrypt_basic, &ctx, ct, pt);
    ok &= check_block("T-table decrypt", aes128_decrypt_ttable, &ctx, ct, pt);
    ok &= check_block("AES-NI decrypt", aes128_decrypt_aesni, &ctx, ct, pt);

    uint8_t in8[128], out8[128];
    for (unsigned i = 0; i < 8; ++i) {
        memcpy(in8 + 16*i, pt, 16);
    }
    aes128_encrypt8_vaes(&ctx, in8, out8);
    for (unsigned i = 0; i < 8; ++i) {
        if (!equal16(out8 + 16*i, ct)) {
            ok = 0;
        }
    }
    printf("[%-20s] %s\n", "VAES x8 encrypt", ok ? "PASS" : "FAIL");

    if (!ok) {
        fprintf(stderr, "At least one correctness test failed; benchmark aborted.\n");
        return EXIT_FAILURE;
    }

    if (system("mkdir -p results") != 0) {
        fprintf(stderr, "warning: could not create results directory\n");
    }
    FILE *csv = fopen("results/aes_benchmark.csv", "w");
    if (csv != NULL) {
        fputs("implementation,mib_per_second\n", csv);
    }

    const size_t bytes = bench_mib * 1024U * 1024U;
    printf("\nBenchmark size: %zu MiB per implementation\n", bench_mib);
    bench_block("AES-128 basic", aes128_encrypt_basic, &ctx, bytes, csv);
    bench_block("AES-128 T-table", aes128_encrypt_ttable, &ctx, bytes, csv);
    bench_block("AES-128 shuffle", aes128_encrypt_shuffle, &ctx, bytes, csv);
    bench_block("AES-128 AES-NI", aes128_encrypt_aesni, &ctx, bytes, csv);
    bench_vaes(&ctx, bytes - (bytes % 128U), csv);

    if (csv != NULL) {
        fclose(csv);
        puts("\nCSV written to results/aes_benchmark.csv");
    }
    return EXIT_SUCCESS;
}
