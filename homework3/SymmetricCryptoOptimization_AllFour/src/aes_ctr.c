#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "aes_ctr.h"

typedef void (*aes_block_encrypt_fn)(const aes128_ctx *,
                                     const uint8_t[16], uint8_t[16]);

static void increment_counter_be(uint8_t counter[16]) {
    for (int i = 15; i >= 0; --i) {
        counter[i] = (uint8_t)(counter[i] + 1U);
        if (counter[i] != 0U) {
            break;
        }
    }
}

static void add_counter_be(uint8_t counter[16], unsigned amount) {
    while (amount-- != 0U) {
        increment_counter_be(counter);
    }
}

static void ctr_crypt_serial(const aes128_ctx *ctx,
                             const uint8_t initial_counter[16],
                             const uint8_t *in, uint8_t *out, size_t len,
                             aes_block_encrypt_fn encrypt_block) {
    uint8_t counter[16];
    uint8_t stream[16];
    memcpy(counter, initial_counter, sizeof(counter));

    while (len != 0U) {
        const size_t take = len < 16U ? len : 16U;
        encrypt_block(ctx, counter, stream);
        for (size_t i = 0; i < take; ++i) {
            out[i] = (uint8_t)(in[i] ^ stream[i]);
        }
        in += take;
        out += take;
        len -= take;
        increment_counter_be(counter);
    }
}

void aes128_ctr_crypt_basic(const aes128_ctx *ctx,
                            const uint8_t initial_counter[16],
                            const uint8_t *in, uint8_t *out, size_t len) {
    ctr_crypt_serial(ctx, initial_counter, in, out, len,
                     aes128_encrypt_basic);
}

void aes128_ctr_crypt_ttable(const aes128_ctx *ctx,
                             const uint8_t initial_counter[16],
                             const uint8_t *in, uint8_t *out, size_t len) {
    ctr_crypt_serial(ctx, initial_counter, in, out, len,
                     aes128_encrypt_ttable);
}

void aes128_ctr_crypt_shuffle(const aes128_ctx *ctx,
                              const uint8_t initial_counter[16],
                              const uint8_t *in, uint8_t *out, size_t len) {
    ctr_crypt_serial(ctx, initial_counter, in, out, len,
                     aes128_encrypt_shuffle);
}

void aes128_ctr_crypt_aesni(const aes128_ctx *ctx,
                            const uint8_t initial_counter[16],
                            const uint8_t *in, uint8_t *out, size_t len) {
    ctr_crypt_serial(ctx, initial_counter, in, out, len,
                     aes128_encrypt_aesni);
}

void aes128_ctr_crypt_vaes8(const aes128_ctx *ctx,
                            const uint8_t initial_counter[16],
                            const uint8_t *in, uint8_t *out, size_t len) {
    uint8_t counter[16];
    uint8_t counters[8 * 16];
    uint8_t stream[8 * 16];
    memcpy(counter, initial_counter, sizeof(counter));

    while (len >= sizeof(counters)) {
        uint8_t current[16];
        memcpy(current, counter, sizeof(current));
        for (unsigned block = 0; block < 8; ++block) {
            memcpy(counters + 16U * block, current, 16);
            increment_counter_be(current);
        }

        aes128_encrypt8_vaes(ctx, counters, stream);
        for (size_t i = 0; i < sizeof(counters); ++i) {
            out[i] = (uint8_t)(in[i] ^ stream[i]);
        }

        add_counter_be(counter, 8);
        in += sizeof(counters);
        out += sizeof(counters);
        len -= sizeof(counters);
    }

    if (len != 0U) {
        ctr_crypt_serial(ctx, counter, in, out, len, aes128_encrypt_aesni);
    }
}
