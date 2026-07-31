#include <immintrin.h>
#include "aes.h"

static inline __m256i broadcast_rk(const uint8_t *rk) {
    const __m128i k = _mm_loadu_si128((const __m128i *)rk);
    return _mm256_broadcastsi128_si256(k);
}

void aes128_encrypt8_vaes(const aes128_ctx *ctx,
                          const uint8_t in[128], uint8_t out[128]) {
    __m256i s0 = _mm256_loadu_si256((const __m256i *)(in + 0));
    __m256i s1 = _mm256_loadu_si256((const __m256i *)(in + 32));
    __m256i s2 = _mm256_loadu_si256((const __m256i *)(in + 64));
    __m256i s3 = _mm256_loadu_si256((const __m256i *)(in + 96));

    __m256i rk = broadcast_rk(ctx->round_keys);
    s0 = _mm256_xor_si256(s0, rk);
    s1 = _mm256_xor_si256(s1, rk);
    s2 = _mm256_xor_si256(s2, rk);
    s3 = _mm256_xor_si256(s3, rk);

    for (unsigned round = 1; round < 10; ++round) {
        rk = broadcast_rk(ctx->round_keys + 16*round);
        s0 = _mm256_aesenc_epi128(s0, rk);
        s1 = _mm256_aesenc_epi128(s1, rk);
        s2 = _mm256_aesenc_epi128(s2, rk);
        s3 = _mm256_aesenc_epi128(s3, rk);
    }

    rk = broadcast_rk(ctx->round_keys + 160);
    s0 = _mm256_aesenclast_epi128(s0, rk);
    s1 = _mm256_aesenclast_epi128(s1, rk);
    s2 = _mm256_aesenclast_epi128(s2, rk);
    s3 = _mm256_aesenclast_epi128(s3, rk);

    _mm256_storeu_si256((__m256i *)(out + 0), s0);
    _mm256_storeu_si256((__m256i *)(out + 32), s1);
    _mm256_storeu_si256((__m256i *)(out + 64), s2);
    _mm256_storeu_si256((__m256i *)(out + 96), s3);
}

void aes128_decrypt8_vaes(const aes128_ctx *ctx,
                          const uint8_t in[128], uint8_t out[128]) {
    __m256i s0 = _mm256_loadu_si256((const __m256i *)(in + 0));
    __m256i s1 = _mm256_loadu_si256((const __m256i *)(in + 32));
    __m256i s2 = _mm256_loadu_si256((const __m256i *)(in + 64));
    __m256i s3 = _mm256_loadu_si256((const __m256i *)(in + 96));

    __m256i rk = broadcast_rk(ctx->round_keys + 160);
    s0 = _mm256_xor_si256(s0, rk);
    s1 = _mm256_xor_si256(s1, rk);
    s2 = _mm256_xor_si256(s2, rk);
    s3 = _mm256_xor_si256(s3, rk);

    for (int round = 9; round >= 1; --round) {
        const __m128i k128 = _mm_loadu_si128(
            (const __m128i *)(ctx->round_keys + 16*round));
        rk = _mm256_broadcastsi128_si256(_mm_aesimc_si128(k128));
        s0 = _mm256_aesdec_epi128(s0, rk);
        s1 = _mm256_aesdec_epi128(s1, rk);
        s2 = _mm256_aesdec_epi128(s2, rk);
        s3 = _mm256_aesdec_epi128(s3, rk);
    }

    rk = broadcast_rk(ctx->round_keys);
    s0 = _mm256_aesdeclast_epi128(s0, rk);
    s1 = _mm256_aesdeclast_epi128(s1, rk);
    s2 = _mm256_aesdeclast_epi128(s2, rk);
    s3 = _mm256_aesdeclast_epi128(s3, rk);

    _mm256_storeu_si256((__m256i *)(out + 0), s0);
    _mm256_storeu_si256((__m256i *)(out + 32), s1);
    _mm256_storeu_si256((__m256i *)(out + 64), s2);
    _mm256_storeu_si256((__m256i *)(out + 96), s3);
}
