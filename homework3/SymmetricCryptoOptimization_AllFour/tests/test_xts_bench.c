#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aes_xts.h"

typedef int (*xts_fn)(const aes128_xts_ctx *, const uint8_t[16],
                      const uint8_t *, uint8_t *, size_t);

static double now_seconds(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        perror("clock_gettime"); exit(EXIT_FAILURE);
    }
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

static int equal(const uint8_t *a, const uint8_t *b, size_t n) {
    uint8_t d = 0;
    for (size_t i = 0; i < n; ++i) d |= (uint8_t)(a[i] ^ b[i]);
    return d == 0U;
}

static int check(const char *name, xts_fn enc, xts_fn dec,
                 const aes128_xts_ctx *ctx, const uint8_t tweak[16],
                 const uint8_t *pt, const uint8_t *expected, size_t len) {
    uint8_t *ct = malloc(len), *out = malloc(len), *inplace = malloc(len);
    if (ct == NULL || out == NULL || inplace == NULL) {
        free(ct); free(out); free(inplace); return 0;
    }
    int ok = enc(ctx, tweak, pt, ct, len) == 0 && equal(ct, expected, len);
    ok &= dec(ctx, tweak, ct, out, len) == 0 && equal(out, pt, len);
    memcpy(inplace, pt, len);
    ok &= enc(ctx, tweak, inplace, inplace, len) == 0 && equal(inplace, expected, len);
    ok &= dec(ctx, tweak, inplace, inplace, len) == 0 && equal(inplace, pt, len);
    printf("[%-25s] %s\n", name, ok ? "PASS" : "FAIL");
    free(ct); free(out); free(inplace);
    return ok;
}

static double bench(const char *name, xts_fn fn, const aes128_xts_ctx *ctx,
                    const uint8_t tweak[16], const uint8_t *in, uint8_t *out,
                    size_t bytes, FILE *csv) {
    const double start = now_seconds();
    const int rc = fn(ctx, tweak, in, out, bytes);
    const double elapsed = now_seconds() - start;
    if (rc != 0) return 0.0;
    const double speed = ((double)bytes/(1024.0*1024.0))/elapsed;
    printf("%-28s %10.2f MiB/s checksum=%02x\n", name, speed, out[bytes-1]);
    if (csv != NULL) fprintf(csv, "%s,%.6f\n", name, speed);
    return speed;
}

int main(int argc, char **argv) {
    size_t mib = 64;
    if (argc == 2) {
        char *end = NULL; errno = 0;
        const unsigned long v = strtoul(argv[1], &end, 10);
        if (errno || end == argv[1] || *end || v == 0) return EXIT_FAILURE;
        mib = (size_t)v;
    }
    uint8_t key1[16], key2[16];
    for (unsigned i = 0; i < 16; ++i) { key1[i]=(uint8_t)i; key2[i]=(uint8_t)(16+i); }
    const uint8_t tweak[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    const uint8_t pt64[64] = {
0x03,0x0a,0x11,0x18,0x1f,0x26,0x2d,0x34,0x3b,0x42,0x49,0x50,0x57,0x5e,0x65,0x6c,
0x73,0x7a,0x81,0x88,0x8f,0x96,0x9d,0xa4,0xab,0xb2,0xb9,0xc0,0xc7,0xce,0xd5,0xdc,
0xe3,0xea,0xf1,0xf8,0xff,0x06,0x0d,0x14,0x1b,0x22,0x29,0x30,0x37,0x3e,0x45,0x4c,
0x53,0x5a,0x61,0x68,0x6f,0x76,0x7d,0x84,0x8b,0x92,0x99,0xa0,0xa7,0xae,0xb5,0xbc};
    const uint8_t ct64[64] = {
0x6a,0x06,0x99,0x2f,0x80,0x2b,0x9b,0xc9,0xc6,0x20,0xc0,0xc8,0xa9,0x11,0x1d,0xba,
0x3b,0x01,0x11,0x30,0xde,0x74,0x7e,0x13,0xe5,0x4a,0xac,0x97,0x31,0x7b,0x83,0xb6,
0xf2,0x03,0x2b,0xde,0xff,0x6e,0xbd,0xfc,0x9b,0x1a,0x99,0x0c,0xee,0xd6,0x8a,0xaf,
0x6f,0x4d,0x42,0x7c,0xc6,0xf5,0x65,0x0c,0xdb,0x41,0x5b,0x9f,0x5c,0x1b,0x87,0xd9};
    const uint8_t pt37[37] = {
0x03,0x0a,0x11,0x18,0x1f,0x26,0x2d,0x34,0x3b,0x42,0x49,0x50,0x57,0x5e,0x65,0x6c,
0x73,0x7a,0x81,0x88,0x8f,0x96,0x9d,0xa4,0xab,0xb2,0xb9,0xc0,0xc7,0xce,0xd5,0xdc,
0xe3,0xea,0xf1,0xf8,0xff};
    const uint8_t ct37[37] = {
0x6a,0x06,0x99,0x2f,0x80,0x2b,0x9b,0xc9,0xc6,0x20,0xc0,0xc8,0xa9,0x11,0x1d,0xba,
0x41,0x1e,0x1e,0x07,0x47,0x69,0x0d,0x69,0x84,0x85,0xeb,0x0b,0xa2,0xde,0x7d,0x83,
0x3b,0x01,0x11,0x30,0xde};

    aes128_xts_ctx ctx;
    if (aes128_xts_init(&ctx, key1, key2) != 0) return EXIT_FAILURE;
    puts("AES-128-XTS known-answer tests (cross-checked with OpenSSL/cryptography)");
    int ok = 1;
    ok &= check("basic full blocks", aes128_xts_encrypt_basic, aes128_xts_decrypt_basic,
                &ctx, tweak, pt64, ct64, sizeof(pt64));
    ok &= check("AES-NI full blocks", aes128_xts_encrypt_aesni, aes128_xts_decrypt_aesni,
                &ctx, tweak, pt64, ct64, sizeof(pt64));
    ok &= check("VAES x8 full blocks", aes128_xts_encrypt_vaes8, aes128_xts_decrypt_vaes8,
                &ctx, tweak, pt64, ct64, sizeof(pt64));
    ok &= check("basic CTS tail", aes128_xts_encrypt_basic, aes128_xts_decrypt_basic,
                &ctx, tweak, pt37, ct37, sizeof(pt37));
    ok &= check("AES-NI CTS tail", aes128_xts_encrypt_aesni, aes128_xts_decrypt_aesni,
                &ctx, tweak, pt37, ct37, sizeof(pt37));
    ok &= check("VAES x8 CTS tail", aes128_xts_encrypt_vaes8, aes128_xts_decrypt_vaes8,
                &ctx, tweak, pt37, ct37, sizeof(pt37));
    if (!ok) return EXIT_FAILURE;

    const size_t bytes = mib * 1024U * 1024U;
    uint8_t *in = aligned_alloc(32, (bytes+31U)&~(size_t)31U);
    uint8_t *out = aligned_alloc(32, (bytes+31U)&~(size_t)31U);
    if (in == NULL || out == NULL) { free(in); free(out); return EXIT_FAILURE; }
    for (size_t i = 0; i < bytes; ++i) in[i]=(uint8_t)(i*17U+5U);
    if (system("mkdir -p results") != 0) {
        fputs("warning: could not create results directory\n", stderr);
    }
    FILE *csv=fopen("results/xts_benchmark.csv","w");
    if (csv) fputs("implementation,mib_per_second\n",csv);
    printf("\nXTS benchmark size: %zu MiB\n", mib);
    bench("AES-XTS basic", aes128_xts_encrypt_basic, &ctx, tweak, in, out, bytes, csv);
    bench("AES-XTS AES-NI", aes128_xts_encrypt_aesni, &ctx, tweak, in, out, bytes, csv);
    bench("AES-XTS VAES x8", aes128_xts_encrypt_vaes8, &ctx, tweak, in, out, bytes, csv);
    if (csv) fclose(csv);
    free(in); free(out);
    return EXIT_SUCCESS;
}
