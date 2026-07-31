#include <immintrin.h>
#include "aes.h"

void aes128_encrypt_aesni(const aes128_ctx *ctx,
                          const uint8_t in[16], uint8_t out[16]) {
    __m128i s = _mm_loadu_si128((const __m128i *)in);
    s = _mm_xor_si128(
        s, _mm_loadu_si128((const __m128i *)ctx->round_keys));
    for (unsigned round = 1; round < 10; ++round) {
        s = _mm_aesenc_si128(
            s,
            _mm_loadu_si128((const __m128i *)(ctx->round_keys + 16*round)));
    }
    s = _mm_aesenclast_si128(
        s, _mm_loadu_si128((const __m128i *)(ctx->round_keys + 160)));
    _mm_storeu_si128((__m128i *)out, s);
}

void aes128_decrypt_aesni(const aes128_ctx *ctx,
                          const uint8_t in[16], uint8_t out[16]) {
    __m128i s = _mm_loadu_si128((const __m128i *)in);
    s = _mm_xor_si128(
        s, _mm_loadu_si128((const __m128i *)(ctx->round_keys + 160)));

    for (int round = 9; round >= 1; --round) {
        __m128i rk = _mm_loadu_si128(
            (const __m128i *)(ctx->round_keys + 16*round));
        rk = _mm_aesimc_si128(rk);
        s = _mm_aesdec_si128(s, rk);
    }

    s = _mm_aesdeclast_si128(
        s, _mm_loadu_si128((const __m128i *)ctx->round_keys));
    _mm_storeu_si128((__m128i *)out, s);
}
