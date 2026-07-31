#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include "sm3_internal.h"

#define VROTL32(x,n) _mm256_or_si256(_mm256_slli_epi32((x),(n)), _mm256_srli_epi32((x),32-(n)))
#define VXOR3(a,b,c) _mm256_xor_si256(_mm256_xor_si256((a),(b)),(c))

static inline __m256i vp0(__m256i x) {
    return VXOR3(x, VROTL32(x,9), VROTL32(x,17));
}

static inline __m256i vp1(__m256i x) {
    return VXOR3(x, VROTL32(x,15), VROTL32(x,23));
}

static inline __m256i vff1(__m256i a, __m256i b, __m256i c) {
    return _mm256_or_si256(
        _mm256_or_si256(_mm256_and_si256(a,b), _mm256_and_si256(a,c)),
        _mm256_and_si256(b,c));
}

static inline __m256i vgg1(__m256i e, __m256i f, __m256i g) {
    return _mm256_or_si256(_mm256_and_si256(e,f), _mm256_andnot_si256(e,g));
}

static __m256i load_word8(const uint8_t *const blocks[8], unsigned word) {
    uint32_t lanes[8];
    for (unsigned i = 0; i < 8; ++i) {
        lanes[i] = sm3_load_be32(blocks[i] + 4U * word);
    }
    return _mm256_loadu_si256((const __m256i *)lanes);
}

static void compress8(__m256i state[8], const uint8_t *const blocks[8]) {
    __m256i w[68];
    __m256i wp[64];

    for (unsigned j = 0; j < 16; ++j) {
        w[j] = load_word8(blocks, j);
    }
    for (unsigned j = 16; j < 68; ++j) {
        const __m256i x = VXOR3(w[j-16], w[j-9], VROTL32(w[j-3],15));
        w[j] = VXOR3(vp1(x), VROTL32(w[j-13],7), w[j-6]);
    }
    for (unsigned j = 0; j < 64; ++j) {
        wp[j] = _mm256_xor_si256(w[j], w[j+4]);
    }

    __m256i a=state[0], b=state[1], c=state[2], d=state[3];
    __m256i e=state[4], f=state[5], g=state[6], h=state[7];
    const __m256i aa=a, bb=b, cc=c, dd=d, ee=e, ff=f, gg=g, hh=h;

    for (unsigned j = 0; j < 64; ++j) {
        const uint32_t tj0 = j < 16U ? UINT32_C(0x79cc4519) : UINT32_C(0x7a879d8a);
        const __m256i tj = _mm256_set1_epi32((int)sm3_rotl32(tj0, j));
        const __m256i a12 = VROTL32(a,12);
        const __m256i ss1 = VROTL32(_mm256_add_epi32(_mm256_add_epi32(a12,e),tj),7);
        const __m256i ss2 = _mm256_xor_si256(ss1,a12);
        const __m256i ffj = j < 16U ? VXOR3(a,b,c) : vff1(a,b,c);
        const __m256i ggj = j < 16U ? VXOR3(e,f,g) : vgg1(e,f,g);
        const __m256i tt1 = _mm256_add_epi32(
            _mm256_add_epi32(_mm256_add_epi32(ffj,d),ss2),wp[j]);
        const __m256i tt2 = _mm256_add_epi32(
            _mm256_add_epi32(_mm256_add_epi32(ggj,h),ss1),w[j]);

        d=c;
        c=VROTL32(b,9);
        b=a;
        a=tt1;
        h=g;
        g=VROTL32(f,19);
        f=e;
        e=vp0(tt2);
    }

    state[0]=_mm256_xor_si256(aa,a);
    state[1]=_mm256_xor_si256(bb,b);
    state[2]=_mm256_xor_si256(cc,c);
    state[3]=_mm256_xor_si256(dd,d);
    state[4]=_mm256_xor_si256(ee,e);
    state[5]=_mm256_xor_si256(ff,f);
    state[6]=_mm256_xor_si256(gg,g);
    state[7]=_mm256_xor_si256(hh,h);
}

void sm3_mb8_avx2(const uint8_t *const messages[8], size_t len,
                  uint8_t digests[8][SM3_DIGEST_SIZE]) {
    __m256i state[8] = {
        _mm256_set1_epi32((int)SM3_IV0), _mm256_set1_epi32((int)SM3_IV1),
        _mm256_set1_epi32((int)SM3_IV2), _mm256_set1_epi32((int)SM3_IV3),
        _mm256_set1_epi32((int)SM3_IV4), _mm256_set1_epi32((int)SM3_IV5),
        _mm256_set1_epi32((int)SM3_IV6), _mm256_set1_epi32((int)SM3_IV7)
    };

    const size_t full = len / 64U;
    for (size_t block = 0; block < full; ++block) {
        const uint8_t *ptrs[8];
        for (unsigned lane = 0; lane < 8; ++lane) {
            ptrs[lane] = messages[lane] + block * 64U;
        }
        compress8(state, ptrs);
    }

    uint8_t tail[8][128];
    unsigned tail_blocks = 0;
    for (unsigned lane = 0; lane < 8; ++lane) {
        const unsigned n = sm3_prepare_tail(messages[lane], len, tail[lane]);
        if (lane == 0U) {
            tail_blocks = n;
        }
    }
    for (unsigned block = 0; block < tail_blocks; ++block) {
        const uint8_t *ptrs[8];
        for (unsigned lane = 0; lane < 8; ++lane) {
            ptrs[lane] = tail[lane] + 64U * block;
        }
        compress8(state, ptrs);
    }

    uint32_t lanes[8];
    for (unsigned word = 0; word < 8; ++word) {
        _mm256_storeu_si256((__m256i *)lanes, state[word]);
        for (unsigned lane = 0; lane < 8; ++lane) {
            sm3_store_be32(digests[lane] + 4U * word, lanes[lane]);
        }
    }
}
