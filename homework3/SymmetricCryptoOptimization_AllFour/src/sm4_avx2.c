#include <immintrin.h>
#include "sm4_internal.h"

static __m256i ttable8(__m256i x) {
    const __m256i mask = _mm256_set1_epi32(0xff);
    const __m256i i0 = _mm256_and_si256(_mm256_srli_epi32(x,24), mask);
    const __m256i i1 = _mm256_and_si256(_mm256_srli_epi32(x,16), mask);
    const __m256i i2 = _mm256_and_si256(_mm256_srli_epi32(x,8), mask);
    const __m256i i3 = _mm256_and_si256(x, mask);
    const __m256i a = _mm256_i32gather_epi32((const int *)SM4_T0, i0, 4);
    const __m256i b = _mm256_i32gather_epi32((const int *)SM4_T1, i1, 4);
    const __m256i c = _mm256_i32gather_epi32((const int *)SM4_T2, i2, 4);
    const __m256i d = _mm256_i32gather_epi32((const int *)SM4_T3, i3, 4);
    return _mm256_xor_si256(_mm256_xor_si256(a,b),
                            _mm256_xor_si256(c,d));
}

static void crypt8(const uint32_t rk[32],
                   const uint8_t in[128], uint8_t out[128]) {
    uint32_t a0[8], a1[8], a2[8], a3[8];
    for (unsigned b = 0; b < 8; ++b) {
        a0[b] = sm4_load_be32(in + 16U*b);
        a1[b] = sm4_load_be32(in + 16U*b + 4);
        a2[b] = sm4_load_be32(in + 16U*b + 8);
        a3[b] = sm4_load_be32(in + 16U*b + 12);
    }

    __m256i x0 = _mm256_loadu_si256((const __m256i *)a0);
    __m256i x1 = _mm256_loadu_si256((const __m256i *)a1);
    __m256i x2 = _mm256_loadu_si256((const __m256i *)a2);
    __m256i x3 = _mm256_loadu_si256((const __m256i *)a3);

    for (unsigned i = 0; i < 32; ++i) {
        __m256i t = _mm256_xor_si256(x1, x2);
        t = _mm256_xor_si256(t, x3);
        t = _mm256_xor_si256(t, _mm256_set1_epi32((int)rk[i]));
        const __m256i n = _mm256_xor_si256(x0, ttable8(t));
        x0=x1; x1=x2; x2=x3; x3=n;
    }

    _mm256_storeu_si256((__m256i *)a0, x0);
    _mm256_storeu_si256((__m256i *)a1, x1);
    _mm256_storeu_si256((__m256i *)a2, x2);
    _mm256_storeu_si256((__m256i *)a3, x3);
    for (unsigned b = 0; b < 8; ++b) {
        sm4_store_be32(out + 16U*b, a3[b]);
        sm4_store_be32(out + 16U*b + 4, a2[b]);
        sm4_store_be32(out + 16U*b + 8, a1[b]);
        sm4_store_be32(out + 16U*b + 12, a0[b]);
    }
}

void sm4_encrypt8_avx2(const sm4_ctx *ctx,
                       const uint8_t in[128], uint8_t out[128]) {
    crypt8(ctx->rk_enc, in, out);
}

void sm4_decrypt8_avx2(const sm4_ctx *ctx,
                       const uint8_t in[128], uint8_t out[128]) {
    crypt8(ctx->rk_dec, in, out);
}
