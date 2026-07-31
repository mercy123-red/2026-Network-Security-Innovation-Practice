#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include "sm3_internal.h"

#define VROTL32(x,n) _mm512_or_si512(_mm512_slli_epi32((x),(n)), _mm512_srli_epi32((x),32-(n)))
#define VXOR3(a,b,c) _mm512_xor_si512(_mm512_xor_si512((a),(b)),(c))

static inline __m512i vp0(__m512i x) {
    return VXOR3(x, VROTL32(x,9), VROTL32(x,17));
}

static inline __m512i vp1(__m512i x) {
    return VXOR3(x, VROTL32(x,15), VROTL32(x,23));
}

static inline __m512i vff1(__m512i a, __m512i b, __m512i c) {
    return _mm512_or_si512(
        _mm512_or_si512(_mm512_and_si512(a,b), _mm512_and_si512(a,c)),
        _mm512_and_si512(b,c));
}

static inline __m512i vgg1(__m512i e, __m512i f, __m512i g) {
    return _mm512_or_si512(_mm512_and_si512(e,f), _mm512_andnot_si512(e,g));
}

static __m512i load_word16(const uint8_t *const blocks[16], unsigned word) {
    uint32_t lanes[16];
    for (unsigned i = 0; i < 16; ++i) {
        lanes[i] = sm3_load_be32(blocks[i] + 4U * word);
    }
    return _mm512_loadu_si512((const void *)lanes);
}

static void compress16(__m512i state[8], const uint8_t *const blocks[16]) {
    __m512i w[68];
    __m512i wp[64];

    for (unsigned j = 0; j < 16; ++j) {
        w[j] = load_word16(blocks, j);
    }
    for (unsigned j = 16; j < 68; ++j) {
        const __m512i x = VXOR3(w[j-16], w[j-9], VROTL32(w[j-3],15));
        w[j] = VXOR3(vp1(x), VROTL32(w[j-13],7), w[j-6]);
    }
    for (unsigned j = 0; j < 64; ++j) {
        wp[j] = _mm512_xor_si512(w[j], w[j+4]);
    }

    __m512i a=state[0], b=state[1], c=state[2], d=state[3];
    __m512i e=state[4], f=state[5], g=state[6], h=state[7];
    const __m512i aa=a, bb=b, cc=c, dd=d, ee=e, ff=f, gg=g, hh=h;

    for (unsigned j = 0; j < 64; ++j) {
        const uint32_t tj0 = j < 16U ? UINT32_C(0x79cc4519) : UINT32_C(0x7a879d8a);
        const __m512i tj = _mm512_set1_epi32((int)sm3_rotl32(tj0, j));
        const __m512i a12 = VROTL32(a,12);
        const __m512i ss1 = VROTL32(_mm512_add_epi32(_mm512_add_epi32(a12,e),tj),7);
        const __m512i ss2 = _mm512_xor_si512(ss1,a12);
        const __m512i ffj = j < 16U ? VXOR3(a,b,c) : vff1(a,b,c);
        const __m512i ggj = j < 16U ? VXOR3(e,f,g) : vgg1(e,f,g);
        const __m512i tt1 = _mm512_add_epi32(
            _mm512_add_epi32(_mm512_add_epi32(ffj,d),ss2),wp[j]);
        const __m512i tt2 = _mm512_add_epi32(
            _mm512_add_epi32(_mm512_add_epi32(ggj,h),ss1),w[j]);

        d=c;
        c=VROTL32(b,9);
        b=a;
        a=tt1;
        h=g;
        g=VROTL32(f,19);
        f=e;
        e=vp0(tt2);
    }

    state[0]=_mm512_xor_si512(aa,a);
    state[1]=_mm512_xor_si512(bb,b);
    state[2]=_mm512_xor_si512(cc,c);
    state[3]=_mm512_xor_si512(dd,d);
    state[4]=_mm512_xor_si512(ee,e);
    state[5]=_mm512_xor_si512(ff,f);
    state[6]=_mm512_xor_si512(gg,g);
    state[7]=_mm512_xor_si512(hh,h);
}

void sm3_mb16_avx512(const uint8_t *const messages[16], size_t len,
                     uint8_t digests[16][SM3_DIGEST_SIZE]) {
    __m512i state[8] = {
        _mm512_set1_epi32((int)SM3_IV0), _mm512_set1_epi32((int)SM3_IV1),
        _mm512_set1_epi32((int)SM3_IV2), _mm512_set1_epi32((int)SM3_IV3),
        _mm512_set1_epi32((int)SM3_IV4), _mm512_set1_epi32((int)SM3_IV5),
        _mm512_set1_epi32((int)SM3_IV6), _mm512_set1_epi32((int)SM3_IV7)
    };

    const size_t full = len / 64U;
    for (size_t block = 0; block < full; ++block) {
        const uint8_t *ptrs[16];
        for (unsigned lane = 0; lane < 16; ++lane) {
            ptrs[lane] = messages[lane] + block * 64U;
        }
        compress16(state, ptrs);
    }

    uint8_t tail[16][128];
    unsigned tail_blocks = 0;
    for (unsigned lane = 0; lane < 16; ++lane) {
        const unsigned n = sm3_prepare_tail(messages[lane], len, tail[lane]);
        if (lane == 0U) {
            tail_blocks = n;
        }
    }
    for (unsigned block = 0; block < tail_blocks; ++block) {
        const uint8_t *ptrs[16];
        for (unsigned lane = 0; lane < 16; ++lane) {
            ptrs[lane] = tail[lane] + 64U * block;
        }
        compress16(state, ptrs);
    }

    uint32_t lanes[16];
    for (unsigned word = 0; word < 8; ++word) {
        _mm512_storeu_si512((void *)lanes, state[word]);
        for (unsigned lane = 0; lane < 16; ++lane) {
            sm3_store_be32(digests[lane] + 4U * word, lanes[lane]);
        }
    }
}
