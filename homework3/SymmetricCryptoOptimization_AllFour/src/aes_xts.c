#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "aes_xts.h"

typedef void (*block_fn)(const aes128_ctx *, const uint8_t[16], uint8_t[16]);

enum xts_backend {
    XTS_SERIAL_BASIC,
    XTS_SERIAL_AESNI,
    XTS_VAES8
};

static void xor16(uint8_t out[16], const uint8_t a[16], const uint8_t b[16]) {
    for (unsigned i = 0; i < 16; ++i) {
        out[i] = (uint8_t)(a[i] ^ b[i]);
    }
}

/* XTS uses the little-endian polynomial representation from IEEE 1619. */
static void gf_mul_alpha(uint8_t tweak[16]) {
    unsigned carry = 0;
    for (unsigned i = 0; i < 16; ++i) {
        const unsigned next = (unsigned)(tweak[i] >> 7);
        tweak[i] = (uint8_t)((tweak[i] << 1) | carry);
        carry = next;
    }
    if (carry != 0U) {
        tweak[0] ^= 0x87U;
    }
}

static void crypt_one(const aes128_ctx *key, block_fn fn,
                      const uint8_t tweak[16],
                      const uint8_t in[16], uint8_t out[16]) {
    uint8_t x[16], y[16];
    xor16(x, in, tweak);
    fn(key, x, y);
    xor16(out, y, tweak);
}

int aes128_xts_init(aes128_xts_ctx *ctx,
                    const uint8_t data_key[16],
                    const uint8_t tweak_key[16]) {
    if (ctx == NULL || data_key == NULL || tweak_key == NULL) {
        return -1;
    }
    if (aes128_init(&ctx->data_key, data_key) != 0 ||
        aes128_init(&ctx->tweak_key, tweak_key) != 0) {
        return -1;
    }
    return 0;
}

static int validate(const aes128_xts_ctx *ctx, const uint8_t tweak_input[16],
                    const uint8_t *in, uint8_t *out, size_t len) {
    if (ctx == NULL || tweak_input == NULL || in == NULL || out == NULL ||
        len < 16U) {
        return 0;
    }
    return 1;
}

static void process_full_serial(const aes128_ctx *key, block_fn fn,
                                uint8_t tweak[16],
                                const uint8_t *in, uint8_t *out,
                                size_t blocks) {
    for (size_t i = 0; i < blocks; ++i) {
        crypt_one(key, fn, tweak, in + 16U*i, out + 16U*i);
        gf_mul_alpha(tweak);
    }
}

static void process_full_vaes(const aes128_ctx *key, int decrypt,
                              uint8_t tweak[16],
                              const uint8_t *in, uint8_t *out,
                              size_t blocks) {
    uint8_t x[128], y[128], tweaks[128];

    while (blocks >= 8U) {
        for (unsigned b = 0; b < 8; ++b) {
            memcpy(tweaks + 16U*b, tweak, 16);
            for (unsigned j = 0; j < 16; ++j) {
                x[16U*b+j] = (uint8_t)(in[16U*b+j] ^ tweak[j]);
            }
            gf_mul_alpha(tweak);
        }
        if (decrypt) {
            aes128_decrypt8_vaes(key, x, y);
        } else {
            aes128_encrypt8_vaes(key, x, y);
        }
        for (unsigned i = 0; i < 128; ++i) {
            out[i] = (uint8_t)(y[i] ^ tweaks[i]);
        }
        in += 128;
        out += 128;
        blocks -= 8;
    }

    if (blocks != 0U) {
        process_full_serial(key,
                            decrypt ? aes128_decrypt_aesni
                                    : aes128_encrypt_aesni,
                            tweak, in, out, blocks);
    }
}

static int xts_encrypt_generic(const aes128_xts_ctx *ctx,
                               const uint8_t tweak_input[16],
                               const uint8_t *plaintext,
                               uint8_t *ciphertext, size_t len,
                               enum xts_backend backend) {
    uint8_t tweak[16];
    if (!validate(ctx, tweak_input, plaintext, ciphertext, len)) {
        return -1;
    }

    if (backend == XTS_SERIAL_BASIC) {
        aes128_encrypt_basic(&ctx->tweak_key, tweak_input, tweak);
    } else {
        aes128_encrypt_aesni(&ctx->tweak_key, tweak_input, tweak);
    }

    const size_t full_blocks = len / 16U;
    const size_t tail = len % 16U;
    const size_t normal_blocks = tail == 0U ? full_blocks : full_blocks - 1U;

    if (backend == XTS_VAES8) {
        process_full_vaes(&ctx->data_key, 0, tweak,
                          plaintext, ciphertext, normal_blocks);
    } else {
        const block_fn enc = backend == XTS_SERIAL_BASIC
                           ? aes128_encrypt_basic : aes128_encrypt_aesni;
        process_full_serial(&ctx->data_key, enc, tweak,
                            plaintext, ciphertext, normal_blocks);
    }

    if (tail == 0U) {
        return 0;
    }

    const uint8_t *last_full_in = plaintext + 16U*normal_blocks;
    const uint8_t *partial_in = last_full_in + 16U;
    uint8_t pfull[16], ppartial[16] = {0};
    uint8_t cc[16], pprime[16], next_tweak[16], cfull[16];
    memcpy(pfull, last_full_in, 16);
    memcpy(ppartial, partial_in, tail);

    const block_fn enc = backend == XTS_SERIAL_BASIC
                       ? aes128_encrypt_basic : aes128_encrypt_aesni;
    crypt_one(&ctx->data_key, enc, tweak, pfull, cc);

    memcpy(pprime, ppartial, tail);
    memcpy(pprime + tail, cc + tail, 16U - tail);
    memcpy(next_tweak, tweak, 16);
    gf_mul_alpha(next_tweak);
    crypt_one(&ctx->data_key, enc, next_tweak, pprime, cfull);

    memcpy(ciphertext + 16U*normal_blocks, cfull, 16);
    memcpy(ciphertext + 16U*(normal_blocks + 1U), cc, tail);
    return 0;
}

static int xts_decrypt_generic(const aes128_xts_ctx *ctx,
                               const uint8_t tweak_input[16],
                               const uint8_t *ciphertext,
                               uint8_t *plaintext, size_t len,
                               enum xts_backend backend) {
    uint8_t tweak[16];
    if (!validate(ctx, tweak_input, ciphertext, plaintext, len)) {
        return -1;
    }

    if (backend == XTS_SERIAL_BASIC) {
        aes128_encrypt_basic(&ctx->tweak_key, tweak_input, tweak);
    } else {
        aes128_encrypt_aesni(&ctx->tweak_key, tweak_input, tweak);
    }

    const size_t full_blocks = len / 16U;
    const size_t tail = len % 16U;
    const size_t normal_blocks = tail == 0U ? full_blocks : full_blocks - 1U;

    if (backend == XTS_VAES8) {
        process_full_vaes(&ctx->data_key, 1, tweak,
                          ciphertext, plaintext, normal_blocks);
    } else {
        const block_fn dec = backend == XTS_SERIAL_BASIC
                           ? aes128_decrypt_basic : aes128_decrypt_aesni;
        process_full_serial(&ctx->data_key, dec, tweak,
                            ciphertext, plaintext, normal_blocks);
    }

    if (tail == 0U) {
        return 0;
    }

    const uint8_t *last_full_in = ciphertext + 16U*normal_blocks;
    const uint8_t *partial_in = last_full_in + 16U;
    uint8_t cfull[16], cpartial[16] = {0};
    uint8_t pp[16], cc[16], pfull[16], next_tweak[16];
    memcpy(cfull, last_full_in, 16);
    memcpy(cpartial, partial_in, tail);

    const block_fn dec = backend == XTS_SERIAL_BASIC
                       ? aes128_decrypt_basic : aes128_decrypt_aesni;
    memcpy(next_tweak, tweak, 16);
    gf_mul_alpha(next_tweak);
    crypt_one(&ctx->data_key, dec, next_tweak, cfull, pp);

    memcpy(cc, cpartial, tail);
    memcpy(cc + tail, pp + tail, 16U - tail);
    crypt_one(&ctx->data_key, dec, tweak, cc, pfull);

    memcpy(plaintext + 16U*normal_blocks, pfull, 16);
    memcpy(plaintext + 16U*(normal_blocks + 1U), pp, tail);
    return 0;
}

int aes128_xts_encrypt_basic(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *plaintext,
                             uint8_t *ciphertext, size_t len) {
    return xts_encrypt_generic(ctx, tweak_input, plaintext, ciphertext, len,
                               XTS_SERIAL_BASIC);
}

int aes128_xts_decrypt_basic(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *ciphertext,
                             uint8_t *plaintext, size_t len) {
    return xts_decrypt_generic(ctx, tweak_input, ciphertext, plaintext, len,
                               XTS_SERIAL_BASIC);
}

int aes128_xts_encrypt_aesni(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *plaintext,
                             uint8_t *ciphertext, size_t len) {
    return xts_encrypt_generic(ctx, tweak_input, plaintext, ciphertext, len,
                               XTS_SERIAL_AESNI);
}

int aes128_xts_decrypt_aesni(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *ciphertext,
                             uint8_t *plaintext, size_t len) {
    return xts_decrypt_generic(ctx, tweak_input, ciphertext, plaintext, len,
                               XTS_SERIAL_AESNI);
}

int aes128_xts_encrypt_vaes8(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *plaintext,
                             uint8_t *ciphertext, size_t len) {
    return xts_encrypt_generic(ctx, tweak_input, plaintext, ciphertext, len,
                               XTS_VAES8);
}

int aes128_xts_decrypt_vaes8(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *ciphertext,
                             uint8_t *plaintext, size_t len) {
    return xts_decrypt_generic(ctx, tweak_input, ciphertext, plaintext, len,
                               XTS_VAES8);
}
