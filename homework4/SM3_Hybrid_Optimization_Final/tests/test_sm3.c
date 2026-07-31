#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sm3.h"

static int hex_nibble(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int parse_hex(const char *hex, uint8_t *out, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        const int hi = hex_nibble(hex[2*i]);
        const int lo = hex_nibble(hex[2*i+1]);
        if (hi < 0 || lo < 0) return 0;
        out[i] = (uint8_t)((hi << 4) | lo);
    }
    return hex[2*n] == '\0';
}

static int same(const uint8_t *a, const uint8_t *b, size_t n) {
    unsigned diff = 0;
    for (size_t i = 0; i < n; ++i) diff |= (unsigned)(a[i] ^ b[i]);
    return diff == 0;
}

static void print_hex(const uint8_t *p, size_t n) {
    for (size_t i = 0; i < n; ++i) printf("%02x", p[i]);
}

static int known_answer(const char *name, const uint8_t *msg, size_t len,
                        const char *expected_hex) {
    uint8_t got[32], expected[32];
    if (!parse_hex(expected_hex, expected, sizeof(expected))) return 0;
    sm3_hash(msg, len, got);
    const int ok = same(got, expected, sizeof(got));
    printf("[%-32s] %s", name, ok ? "PASS" : "FAIL");
    if (!ok) {
        printf("\n  expected="); print_hex(expected, 32);
        printf("\n  got     ="); print_hex(got, 32);
    }
    putchar('\n');
    return ok;
}

static void fill_message(uint8_t *p, size_t len, unsigned lane) {
    uint32_t x = UINT32_C(0x9e3779b9) ^ (uint32_t)(lane * UINT32_C(0x1020304));
    for (size_t i = 0; i < len; ++i) {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        p[i] = (uint8_t)(x + (uint32_t)i + lane);
    }
}

static int test_streaming(void) {
    uint8_t msg[1000], one[32], stream[32];
    fill_message(msg, sizeof(msg), 7);
    sm3_hash(msg, sizeof(msg), one);

    sm3_ctx ctx;
    sm3_init(&ctx);
    size_t off = 0;
    const size_t chunks[] = {1, 2, 7, 64, 3, 129, 5, 256, 11};
    unsigned ci = 0;
    while (off < sizeof(msg)) {
        size_t n = chunks[ci++ % (sizeof(chunks)/sizeof(chunks[0]))];
        if (n > sizeof(msg) - off) n = sizeof(msg) - off;
        sm3_update(&ctx, msg + off, n);
        off += n;
    }
    sm3_final(&ctx, stream);
    const int ok = same(one, stream, 32);
    printf("[%-32s] %s\n", "streaming/chunked update", ok ? "PASS" : "FAIL");
    return ok;
}

static int test_backend(sm3_backend backend, size_t len, size_t count) {
    if (!sm3_backend_available(backend)) {
        printf("[%-32s] SKIP (unavailable)\n", sm3_backend_name(backend));
        return 1;
    }

    uint8_t **storage = (uint8_t **)calloc(count, sizeof(*storage));
    const uint8_t **messages = (const uint8_t **)calloc(count, sizeof(*messages));
    uint8_t *expected = (uint8_t *)malloc(count * 32U);
    uint8_t *actual = (uint8_t *)malloc(count * 32U);
    if (!storage || !messages || !expected || !actual) {
        fprintf(stderr, "allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < count; ++i) {
        storage[i] = (uint8_t *)malloc(len == 0U ? 1U : len);
        if (!storage[i]) exit(EXIT_FAILURE);
        fill_message(storage[i], len, (unsigned)i + 1U);
        messages[i] = storage[i];
        sm3_hash(messages[i], len, expected + i * 32U);
    }

    const int rc = sm3_hash_many_equal(messages, count, len, actual, backend);
    const int ok = rc == 0 && same(expected, actual, count * 32U);
    char label[96];
    snprintf(label, sizeof(label), "%s len=%zu count=%zu", sm3_backend_name(backend), len, count);
    printf("[%-32s] %s\n", label, ok ? "PASS" : "FAIL");

    for (size_t i = 0; i < count; ++i) free(storage[i]);
    free(actual); free(expected); free(messages); free(storage);
    return ok;
}

int main(void) {
    int ok = 1;
    static const uint8_t empty[1] = {0};
    static const uint8_t abc[] = {'a','b','c'};
    uint8_t abcd64[64];
    for (unsigned i = 0; i < 16; ++i) memcpy(abcd64 + 4*i, "abcd", 4);

    puts("SM3 scalar known-answer tests");
    ok &= known_answer("empty string", empty, 0,
        "1ab21d8355cfa17f8e61194831e81a8f22bec8c728fefb747ed035eb5082aa2b");
    ok &= known_answer("abc", abc, sizeof(abc),
        "66c7f0f462eeedd9d1f2d46bdc10e4e24167c4875cf2f7a2297da02b8f4ba8e0");
    ok &= known_answer("abcd repeated 16 times", abcd64, sizeof(abcd64),
        "debe9ff92275b8a138604889c18e5a4d6fdb70e5387e5765293dcba39c0c5732");
    ok &= test_streaming();

    puts("\nSIMD/GPR hybrid cross-checks against scalar implementation");
    const size_t lengths[] = {0, 3, 55, 56, 63, 64, 65, 127, 128, 129, 1000};
    const sm3_backend backends[] = {
        SM3_BACKEND_AVX2, SM3_BACKEND_AVX512, SM3_BACKEND_NEON, SM3_BACKEND_AUTO
    };
    for (size_t b = 0; b < sizeof(backends)/sizeof(backends[0]); ++b) {
        for (size_t i = 0; i < sizeof(lengths)/sizeof(lengths[0]); ++i) {
            ok &= test_backend(backends[b], lengths[i], 17);
        }
    }

    printf("\nBest runtime backend: %s\n", sm3_backend_name(sm3_best_backend()));
    puts(ok ? "ALL TESTS PASSED" : "TEST FAILURE");
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
