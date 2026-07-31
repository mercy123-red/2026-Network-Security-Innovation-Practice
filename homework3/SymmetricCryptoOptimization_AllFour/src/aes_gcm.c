#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "aes_gcm.h"

/*
 * GCM field representation follows SP 800-38D: the leftmost bit is the
 * coefficient of x^127.  The PCLMUL implementation reverses all 128 bits,
 * multiplies in CLMUL's little-endian polynomial representation, reduces
 * modulo x^128 + x^7 + x^2 + x + 1, then reverses each byte back.
 */

typedef void (*block_encrypt_fn)(const aes128_ctx *,
                                 const uint8_t[16], uint8_t[16]);
typedef void (*ghash_update_fn)(const uint8_t[16],
                                const uint8_t *, size_t, uint8_t[16]);

enum ctr_backend {
    CTR_AESNI,
    CTR_VAES8
};

static void xor_block(uint8_t out[16], const uint8_t in[16]) {
    for (unsigned i = 0; i < 16; ++i) {
        out[i] ^= in[i];
    }
}

static void store_be64(uint8_t out[8], uint64_t x) {
    for (int i = 7; i >= 0; --i) {
        out[i] = (uint8_t)x;
        x >>= 8;
    }
}

static int bit_length_fits_u64(size_t bytes) {
    return bytes <= (UINT64_MAX / 8U);
}

static void shift_right_one(uint8_t v[16]) {
    uint8_t carry = 0;
    for (unsigned i = 0; i < 16; ++i) {
        const uint8_t next = (uint8_t)(v[i] & 1U);
        v[i] = (uint8_t)((v[i] >> 1) | (uint8_t)(carry << 7));
        carry = next;
    }
}

static void gf_mul_basic(const uint8_t x[16], const uint8_t y[16],
                         uint8_t out[16]) {
    uint8_t z[16] = {0};
    uint8_t v[16];
    memcpy(v, y, 16);

    for (unsigned bit = 0; bit < 128; ++bit) {
        if ((x[bit >> 3] & (uint8_t)(0x80U >> (bit & 7U))) != 0U) {
            xor_block(z, v);
        }
        const uint8_t lsb = (uint8_t)(v[15] & 1U);
        shift_right_one(v);
        if (lsb != 0U) {
            v[0] ^= 0xe1U;
        }
    }
    memcpy(out, z, 16);
}

static __m128i reverse_bits_each_byte(__m128i x) {
    const __m128i nibble_mask = _mm_set1_epi8(0x0f);
    const __m128i reverse_nibble = _mm_setr_epi8(
        0x0,0x8,0x4,0xc,0x2,0xa,0x6,0xe,
        0x1,0x9,0x5,0xd,0x3,0xb,0x7,0xf);
    const __m128i lo = _mm_and_si128(x, nibble_mask);
    const __m128i hi = _mm_and_si128(_mm_srli_epi16(x, 4), nibble_mask);
    const __m128i reversed_bits = _mm_or_si128(
        _mm_slli_epi16(_mm_shuffle_epi8(reverse_nibble, lo), 4),
        _mm_shuffle_epi8(reverse_nibble, hi));
    return reversed_bits;
}

static void gf_mul_pclmul(const uint8_t x[16], const uint8_t y[16],
                          uint8_t out[16]) {
    __m128i a = reverse_bits_each_byte(_mm_loadu_si128((const __m128i *)x));
    __m128i b = reverse_bits_each_byte(_mm_loadu_si128((const __m128i *)y));

    const __m128i z0 = _mm_clmulepi64_si128(a, b, 0x00);
    const __m128i z2 = _mm_clmulepi64_si128(a, b, 0x11);
    const __m128i ax = _mm_xor_si128(a, _mm_srli_si128(a, 8));
    const __m128i bx = _mm_xor_si128(b, _mm_srli_si128(b, 8));
    const __m128i zm = _mm_clmulepi64_si128(ax, bx, 0x00);
    const __m128i z1 = _mm_xor_si128(zm, _mm_xor_si128(z0, z2));

    const uint64_t z0_lo = (uint64_t)_mm_cvtsi128_si64(z0);
    const uint64_t z0_hi = (uint64_t)_mm_extract_epi64(z0, 1);
    const uint64_t z1_lo = (uint64_t)_mm_cvtsi128_si64(z1);
    const uint64_t z1_hi = (uint64_t)_mm_extract_epi64(z1, 1);
    const uint64_t z2_lo = (uint64_t)_mm_cvtsi128_si64(z2);
    const uint64_t z2_hi = (uint64_t)_mm_extract_epi64(z2, 1);

    __extension__ typedef unsigned __int128 u128;
    const u128 low =
        (u128)z0_lo |
        ((u128)(z0_hi ^ z1_lo) << 64);
    const u128 high =
        (u128)(z2_lo ^ z1_hi) |
        ((u128)z2_hi << 64);

    /* Fold high*x^128 with x^128 = x^7 + x^2 + x + 1. */
    const u128 folded_low =
        high ^ (high << 1) ^ (high << 2) ^ (high << 7);
    const u128 overflow =
        (high >> 127) ^ (high >> 126) ^ (high >> 121);
    const u128 folded_overflow =
        overflow ^ (overflow << 1) ^ (overflow << 2) ^ (overflow << 7);
    const u128 reduced = low ^ folded_low ^ folded_overflow;

    const __m128i r = _mm_set_epi64x(
        (long long)(uint64_t)(reduced >> 64),
        (long long)(uint64_t)reduced);
    _mm_storeu_si128((__m128i *)out, reverse_bits_each_byte(r));
}

static void ghash_update_generic(const uint8_t h[16], const uint8_t *data,
                                 size_t len, uint8_t acc[16],
                                 void (*multiply)(const uint8_t[16],
                                                  const uint8_t[16],
                                                  uint8_t[16])) {
    uint8_t block[16];
    while (len >= 16U) {
        xor_block(acc, data);
        multiply(acc, h, acc);
        data += 16;
        len -= 16;
    }
    if (len != 0U) {
        memset(block, 0, sizeof(block));
        memcpy(block, data, len);
        xor_block(acc, block);
        multiply(acc, h, acc);
    }
}

void aes_gcm_ghash_basic(const uint8_t h[16], const uint8_t *data,
                         size_t len, uint8_t accumulator[16]) {
    ghash_update_generic(h, data, len, accumulator, gf_mul_basic);
}

void aes_gcm_ghash_pclmul(const uint8_t h[16], const uint8_t *data,
                          size_t len, uint8_t accumulator[16]) {
    ghash_update_generic(h, data, len, accumulator, gf_mul_pclmul);
}

static void increment_counter32(uint8_t counter[16]) {
    for (int i = 15; i >= 12; --i) {
        counter[i] = (uint8_t)(counter[i] + 1U);
        if (counter[i] != 0U) {
            break;
        }
    }
}

static void ctr32_serial(const aes128_ctx *aes, uint8_t counter[16],
                         const uint8_t *in, uint8_t *out, size_t len,
                         block_encrypt_fn encrypt_block) {
    uint8_t stream[16];
    while (len != 0U) {
        const size_t take = len < 16U ? len : 16U;
        increment_counter32(counter);
        encrypt_block(aes, counter, stream);
        for (size_t i = 0; i < take; ++i) {
            out[i] = (uint8_t)(in[i] ^ stream[i]);
        }
        in += take;
        out += take;
        len -= take;
    }
}

static void ctr32_vaes8(const aes128_ctx *aes, uint8_t counter[16],
                        const uint8_t *in, uint8_t *out, size_t len) {
    uint8_t counters[128];
    uint8_t stream[128];

    while (len >= 128U) {
        for (unsigned block = 0; block < 8; ++block) {
            increment_counter32(counter);
            memcpy(counters + 16U*block, counter, 16);
        }
        aes128_encrypt8_vaes(aes, counters, stream);
        for (unsigned i = 0; i < 128; ++i) {
            out[i] = (uint8_t)(in[i] ^ stream[i]);
        }
        in += 128;
        out += 128;
        len -= 128;
    }
    if (len != 0U) {
        ctr32_serial(aes, counter, in, out, len, aes128_encrypt_aesni);
    }
}

static void compute_j0(const aes128_gcm_ctx *ctx,
                       const uint8_t *iv, size_t iv_len,
                       uint8_t j0[16], ghash_update_fn ghash) {
    if (iv_len == 12U) {
        memcpy(j0, iv, 12);
        j0[12] = 0;
        j0[13] = 0;
        j0[14] = 0;
        j0[15] = 1;
        return;
    }

    uint8_t acc[16] = {0};
    uint8_t lengths[16] = {0};
    ghash(ctx->hash_subkey, iv, iv_len, acc);
    store_be64(lengths + 8, (uint64_t)iv_len * 8U);
    ghash(ctx->hash_subkey, lengths, 16, acc);
    memcpy(j0, acc, 16);
}

static void compute_auth(const aes128_gcm_ctx *ctx,
                         const uint8_t *aad, size_t aad_len,
                         const uint8_t *ciphertext, size_t text_len,
                         uint8_t s[16], ghash_update_fn ghash) {
    uint8_t lengths[16];
    memset(s, 0, 16);
    ghash(ctx->hash_subkey, aad, aad_len, s);
    ghash(ctx->hash_subkey, ciphertext, text_len, s);
    store_be64(lengths, (uint64_t)aad_len * 8U);
    store_be64(lengths + 8, (uint64_t)text_len * 8U);
    ghash(ctx->hash_subkey, lengths, 16, s);
}

static int constant_time_equal16(const uint8_t a[16], const uint8_t b[16]) {
    uint8_t diff = 0;
    for (unsigned i = 0; i < 16; ++i) {
        diff |= (uint8_t)(a[i] ^ b[i]);
    }
    return diff == 0U;
}

static int validate_inputs(const aes128_gcm_ctx *ctx,
                           const uint8_t *iv, size_t iv_len,
                           const uint8_t *aad, size_t aad_len,
                           const uint8_t *in, uint8_t *out,
                           size_t text_len, const uint8_t *tag) {
    if (ctx == NULL || iv == NULL || iv_len == 0U || tag == NULL) {
        return 0;
    }
    if ((aad_len != 0U && aad == NULL) ||
        (text_len != 0U && (in == NULL || out == NULL))) {
        return 0;
    }
    if (!bit_length_fits_u64(iv_len) || !bit_length_fits_u64(aad_len) ||
        !bit_length_fits_u64(text_len)) {
        return 0;
    }
    return 1;
}

static int gcm_encrypt_generic(const aes128_gcm_ctx *ctx,
                               const uint8_t *iv, size_t iv_len,
                               const uint8_t *aad, size_t aad_len,
                               const uint8_t *plaintext, uint8_t *ciphertext,
                               size_t text_len, uint8_t tag[16],
                               ghash_update_fn ghash,
                               enum ctr_backend ctr,
                               block_encrypt_fn tag_encrypt) {
    uint8_t j0[16], counter[16], s[16], mask[16];
    if (!validate_inputs(ctx, iv, iv_len, aad, aad_len,
                         plaintext, ciphertext, text_len, tag)) {
        return -1;
    }

    compute_j0(ctx, iv, iv_len, j0, ghash);
    memcpy(counter, j0, 16);
    if (ctr == CTR_VAES8) {
        ctr32_vaes8(&ctx->aes, counter, plaintext, ciphertext, text_len);
    } else {
        ctr32_serial(&ctx->aes, counter, plaintext, ciphertext, text_len,
                     tag_encrypt);
    }

    compute_auth(ctx, aad, aad_len, ciphertext, text_len, s, ghash);
    tag_encrypt(&ctx->aes, j0, mask);
    for (unsigned i = 0; i < 16; ++i) {
        tag[i] = (uint8_t)(s[i] ^ mask[i]);
    }
    return 0;
}

static int gcm_decrypt_generic(const aes128_gcm_ctx *ctx,
                               const uint8_t *iv, size_t iv_len,
                               const uint8_t *aad, size_t aad_len,
                               const uint8_t *ciphertext, uint8_t *plaintext,
                               size_t text_len, const uint8_t tag[16],
                               ghash_update_fn ghash,
                               enum ctr_backend ctr,
                               block_encrypt_fn tag_encrypt) {
    uint8_t j0[16], counter[16], s[16], mask[16], expected[16];
    if (!validate_inputs(ctx, iv, iv_len, aad, aad_len,
                         ciphertext, plaintext, text_len, tag)) {
        return -1;
    }

    compute_j0(ctx, iv, iv_len, j0, ghash);
    compute_auth(ctx, aad, aad_len, ciphertext, text_len, s, ghash);
    tag_encrypt(&ctx->aes, j0, mask);
    for (unsigned i = 0; i < 16; ++i) {
        expected[i] = (uint8_t)(s[i] ^ mask[i]);
    }
    if (!constant_time_equal16(expected, tag)) {
        if (text_len != 0U) {
            memset(plaintext, 0, text_len);
        }
        return -2;
    }

    memcpy(counter, j0, 16);
    if (ctr == CTR_VAES8) {
        ctr32_vaes8(&ctx->aes, counter, ciphertext, plaintext, text_len);
    } else {
        ctr32_serial(&ctx->aes, counter, ciphertext, plaintext, text_len,
                     tag_encrypt);
    }
    return 0;
}

int aes128_gcm_init(aes128_gcm_ctx *ctx, const uint8_t key[16]) {
    static const uint8_t zero[16] = {0};
    if (ctx == NULL || key == NULL || aes128_init(&ctx->aes, key) != 0) {
        return -1;
    }
    aes128_encrypt_basic(&ctx->aes, zero, ctx->hash_subkey);
    return 0;
}

int aes128_gcm_encrypt_basic(const aes128_gcm_ctx *ctx,
                             const uint8_t *iv, size_t iv_len,
                             const uint8_t *aad, size_t aad_len,
                             const uint8_t *plaintext, uint8_t *ciphertext,
                             size_t text_len, uint8_t tag[16]) {
    return gcm_encrypt_generic(ctx, iv, iv_len, aad, aad_len,
                               plaintext, ciphertext, text_len, tag,
                               aes_gcm_ghash_basic, CTR_AESNI,
                               aes128_encrypt_basic);
}

int aes128_gcm_decrypt_basic(const aes128_gcm_ctx *ctx,
                             const uint8_t *iv, size_t iv_len,
                             const uint8_t *aad, size_t aad_len,
                             const uint8_t *ciphertext, uint8_t *plaintext,
                             size_t text_len, const uint8_t tag[16]) {
    return gcm_decrypt_generic(ctx, iv, iv_len, aad, aad_len,
                               ciphertext, plaintext, text_len, tag,
                               aes_gcm_ghash_basic, CTR_AESNI,
                               aes128_encrypt_basic);
}

int aes128_gcm_encrypt_aesni_pclmul(const aes128_gcm_ctx *ctx,
                                    const uint8_t *iv, size_t iv_len,
                                    const uint8_t *aad, size_t aad_len,
                                    const uint8_t *plaintext,
                                    uint8_t *ciphertext, size_t text_len,
                                    uint8_t tag[16]) {
    return gcm_encrypt_generic(ctx, iv, iv_len, aad, aad_len,
                               plaintext, ciphertext, text_len, tag,
                               aes_gcm_ghash_pclmul, CTR_AESNI,
                               aes128_encrypt_aesni);
}

int aes128_gcm_decrypt_aesni_pclmul(const aes128_gcm_ctx *ctx,
                                    const uint8_t *iv, size_t iv_len,
                                    const uint8_t *aad, size_t aad_len,
                                    const uint8_t *ciphertext,
                                    uint8_t *plaintext, size_t text_len,
                                    const uint8_t tag[16]) {
    return gcm_decrypt_generic(ctx, iv, iv_len, aad, aad_len,
                               ciphertext, plaintext, text_len, tag,
                               aes_gcm_ghash_pclmul, CTR_AESNI,
                               aes128_encrypt_aesni);
}

int aes128_gcm_encrypt_vaes8_pclmul(const aes128_gcm_ctx *ctx,
                                    const uint8_t *iv, size_t iv_len,
                                    const uint8_t *aad, size_t aad_len,
                                    const uint8_t *plaintext,
                                    uint8_t *ciphertext, size_t text_len,
                                    uint8_t tag[16]) {
    return gcm_encrypt_generic(ctx, iv, iv_len, aad, aad_len,
                               plaintext, ciphertext, text_len, tag,
                               aes_gcm_ghash_pclmul, CTR_VAES8,
                               aes128_encrypt_aesni);
}

int aes128_gcm_decrypt_vaes8_pclmul(const aes128_gcm_ctx *ctx,
                                    const uint8_t *iv, size_t iv_len,
                                    const uint8_t *aad, size_t aad_len,
                                    const uint8_t *ciphertext,
                                    uint8_t *plaintext, size_t text_len,
                                    const uint8_t tag[16]) {
    return gcm_decrypt_generic(ctx, iv, iv_len, aad, aad_len,
                               ciphertext, plaintext, text_len, tag,
                               aes_gcm_ghash_pclmul, CTR_VAES8,
                               aes128_encrypt_aesni);
}
