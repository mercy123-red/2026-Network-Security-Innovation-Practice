#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sm3.h"

static double now_seconds(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

static void fill_message(uint8_t *p, size_t len, unsigned lane) {
    uint32_t x = UINT32_C(0x243f6a88) + lane * UINT32_C(0x9e3779b9);
    for (size_t i = 0; i < len; ++i) {
        x = x * UINT32_C(1664525) + UINT32_C(1013904223);
        p[i] = (uint8_t)(x >> 24);
    }
}

static double bench_scalar(const uint8_t *const *messages, size_t lanes,
                           size_t len, uint8_t *digests) {
    const double begin = now_seconds();
    for (size_t lane = 0; lane < lanes; ++lane) {
        sm3_hash(messages[lane], len, digests + lane * 32U);
    }
    const double elapsed = now_seconds() - begin;
    return ((double)(lanes * len) / (1024.0 * 1024.0)) / elapsed;
}

static double bench_backend(const uint8_t *const *messages, size_t lanes,
                            size_t len, uint8_t *digests, sm3_backend backend) {
    const double begin = now_seconds();
    const int rc = sm3_hash_many_equal(messages, lanes, len, digests, backend);
    const double elapsed = now_seconds() - begin;
    if (rc != 0) return -1.0;
    return ((double)(lanes * len) / (1024.0 * 1024.0)) / elapsed;
}

static void emit_result(FILE *csv, const char *implementation, size_t lanes,
                        double throughput, double scalar_throughput,
                        unsigned checksum) {
    const double speedup = throughput / scalar_throughput;
    printf("%-28s lanes=%-2zu %10.2f MiB/s  speedup=%6.2fx checksum=%02x\n",
           implementation, lanes, throughput, speedup, checksum & 0xffU);
    if (csv) {
        fprintf(csv, "%s,%zu,%.6f,%.6f,%u\n",
                implementation, lanes, throughput, speedup, checksum & 0xffU);
    }
}

int main(int argc, char **argv) {
    size_t mib_per_lane = 8;
    if (argc >= 2) {
        char *end = NULL;
        errno = 0;
        const unsigned long v = strtoul(argv[1], &end, 10);
        if (errno != 0 || end == argv[1] || *end != '\0' || v == 0) {
            fprintf(stderr, "usage: %s [MiB-per-lane] [csv-path]\n", argv[0]);
            return EXIT_FAILURE;
        }
        mib_per_lane = (size_t)v;
    }
    const char *csv_path = argc >= 3 ? argv[2] : "results/sm3_benchmark.csv";

    const size_t lanes = 16;
    const size_t len = mib_per_lane * 1024U * 1024U;
    uint8_t **storage = (uint8_t **)calloc(lanes, sizeof(*storage));
    const uint8_t **messages = (const uint8_t **)calloc(lanes, sizeof(*messages));
    uint8_t *digests = (uint8_t *)calloc(lanes, 32U);
    if (!storage || !messages || !digests) {
        fprintf(stderr, "allocation failed\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < lanes; ++i) {
        storage[i] = (uint8_t *)malloc(len);
        if (!storage[i]) return EXIT_FAILURE;
        fill_message(storage[i], len, (unsigned)i);
        messages[i] = storage[i];
    }

    FILE *csv = fopen(csv_path, "w");
    if (!csv) {
        perror(csv_path);
        return EXIT_FAILURE;
    }
    fputs("implementation,lanes,mib_per_second,speedup,checksum\n", csv);

    puts("SM3 equal-length independent-message throughput benchmark");
    printf("Message size: %zu MiB per lane\n", mib_per_lane);

    const double scalar = bench_scalar(messages, lanes, len, digests);
    unsigned checksum = 0;
    for (size_t i = 0; i < lanes * 32U; ++i) checksum ^= digests[i];
    emit_result(csv, "scalar GPR", lanes, scalar, scalar, checksum);

    const sm3_backend backends[] = {
        SM3_BACKEND_AVX2, SM3_BACKEND_AVX512, SM3_BACKEND_NEON, SM3_BACKEND_AUTO
    };
    for (size_t i = 0; i < sizeof(backends)/sizeof(backends[0]); ++i) {
        const sm3_backend backend = backends[i];
        if (!sm3_backend_available(backend)) {
            printf("%-28s SKIP (unavailable)\n", sm3_backend_name(backend));
            continue;
        }
        memset(digests, 0, lanes * 32U);
        const double value = bench_backend(messages, lanes, len, digests, backend);
        checksum = 0;
        for (size_t j = 0; j < lanes * 32U; ++j) checksum ^= digests[j];
        emit_result(csv, sm3_backend_name(backend), lanes, value, scalar, checksum);
    }

    fclose(csv);
    printf("CSV written to %s\n", csv_path);
    for (size_t i = 0; i < lanes; ++i) free(storage[i]);
    free(digests); free(messages); free(storage);
    return EXIT_SUCCESS;
}
