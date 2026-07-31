#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "sm4_ctr.h"

typedef void (*block_fn)(const sm4_ctx *, const uint8_t[16], uint8_t[16]);

static void increment_be(uint8_t c[16]) {
    for (int i = 15; i >= 0; --i) {
        c[i] = (uint8_t)(c[i] + 1U);
        if (c[i] != 0U) break;
    }
}

static void serial(const sm4_ctx *ctx, const uint8_t initial[16],
                   const uint8_t *in, uint8_t *out, size_t len, block_fn fn) {
    uint8_t counter[16], stream[16];
    memcpy(counter, initial, 16);
    while (len != 0U) {
        const size_t take = len < 16U ? len : 16U;
        fn(ctx, counter, stream);
        for (size_t i = 0; i < take; ++i) out[i] = (uint8_t)(in[i] ^ stream[i]);
        in += take; out += take; len -= take;
        increment_be(counter);
    }
}

void sm4_ctr_crypt_basic(const sm4_ctx *ctx, const uint8_t initial[16],
                         const uint8_t *in, uint8_t *out, size_t len) {
    serial(ctx, initial, in, out, len, sm4_encrypt_basic);
}

void sm4_ctr_crypt_ttable(const sm4_ctx *ctx, const uint8_t initial[16],
                          const uint8_t *in, uint8_t *out, size_t len) {
    serial(ctx, initial, in, out, len, sm4_encrypt_ttable);
}

void sm4_ctr_crypt_avx2(const sm4_ctx *ctx, const uint8_t initial[16],
                        const uint8_t *in, uint8_t *out, size_t len) {
    uint8_t counter[16], counters[128], stream[128];
    memcpy(counter, initial, 16);
    while (len >= 128U) {
        for (unsigned b = 0; b < 8; ++b) {
            memcpy(counters + 16U*b, counter, 16);
            increment_be(counter);
        }
        sm4_encrypt8_avx2(ctx, counters, stream);
        for (unsigned i = 0; i < 128; ++i) out[i] = (uint8_t)(in[i] ^ stream[i]);
        in += 128; out += 128; len -= 128;
    }
    if (len != 0U) serial(ctx, counter, in, out, len, sm4_encrypt_ttable);
}
