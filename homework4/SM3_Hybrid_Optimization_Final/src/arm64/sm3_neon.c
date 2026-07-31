#include <arm_neon.h>
#include <stddef.h>
#include <stdint.h>
#include "sm3_internal.h"

#define VROTL32(x,n) vorrq_u32(vshlq_n_u32((x),(n)), vshrq_n_u32((x),32-(n)))
#define VXOR3(a,b,c) veorq_u32(veorq_u32((a),(b)),(c))

static inline uint32x4_t vp0(uint32x4_t x) {
    return VXOR3(x, VROTL32(x,9), VROTL32(x,17));
}

static inline uint32x4_t vp1(uint32x4_t x) {
    return VXOR3(x, VROTL32(x,15), VROTL32(x,23));
}

static inline uint32x4_t vff1(uint32x4_t a, uint32x4_t b, uint32x4_t c) {
    return vorrq_u32(vorrq_u32(vandq_u32(a,b), vandq_u32(a,c)), vandq_u32(b,c));
}

static inline uint32x4_t vgg1(uint32x4_t e, uint32x4_t f, uint32x4_t g) {
    return vorrq_u32(vandq_u32(e,f), vbicq_u32(g,e));
}

static uint32x4_t load_word4(const uint8_t *const blocks[4], unsigned word) {
    uint32_t lanes[4];
    for (unsigned i = 0; i < 4; ++i) {
        lanes[i] = sm3_load_be32(blocks[i] + 4U * word);
    }
    return vld1q_u32(lanes);
}

static void compress4(uint32x4_t state[8], const uint8_t *const blocks[4]) {
    uint32x4_t w[68];
    uint32x4_t wp[64];

    for (unsigned j = 0; j < 16; ++j) {
        w[j] = load_word4(blocks, j);
    }
    for (unsigned j = 16; j < 68; ++j) {
        const uint32x4_t x = VXOR3(w[j-16], w[j-9], VROTL32(w[j-3],15));
        w[j] = VXOR3(vp1(x), VROTL32(w[j-13],7), w[j-6]);
    }
    for (unsigned j = 0; j < 64; ++j) {
        wp[j] = veorq_u32(w[j], w[j+4]);
    }

    uint32x4_t a=state[0], b=state[1], c=state[2], d=state[3];
    uint32x4_t e=state[4], f=state[5], g=state[6], h=state[7];
    const uint32x4_t aa=a, bb=b, cc=c, dd=d, ee=e, ff=f, gg=g, hh=h;

    for (unsigned j = 0; j < 64; ++j) {
        const uint32_t tj0 = j < 16U ? UINT32_C(0x79cc4519) : UINT32_C(0x7a879d8a);
        const uint32x4_t tj = vdupq_n_u32(sm3_rotl32(tj0, j));
        const uint32x4_t a12 = VROTL32(a,12);
        const uint32x4_t ss1 = VROTL32(vaddq_u32(vaddq_u32(a12,e),tj),7);
        const uint32x4_t ss2 = veorq_u32(ss1,a12);
        const uint32x4_t ffj = j < 16U ? VXOR3(a,b,c) : vff1(a,b,c);
        const uint32x4_t ggj = j < 16U ? VXOR3(e,f,g) : vgg1(e,f,g);
        const uint32x4_t tt1 = vaddq_u32(vaddq_u32(vaddq_u32(ffj,d),ss2),wp[j]);
        const uint32x4_t tt2 = vaddq_u32(vaddq_u32(vaddq_u32(ggj,h),ss1),w[j]);

        d=c;
        c=VROTL32(b,9);
        b=a;
        a=tt1;
        h=g;
        g=VROTL32(f,19);
        f=e;
        e=vp0(tt2);
    }

    state[0]=veorq_u32(aa,a);
    state[1]=veorq_u32(bb,b);
    state[2]=veorq_u32(cc,c);
    state[3]=veorq_u32(dd,d);
    state[4]=veorq_u32(ee,e);
    state[5]=veorq_u32(ff,f);
    state[6]=veorq_u32(gg,g);
    state[7]=veorq_u32(hh,h);
}

void sm3_mb4_neon(const uint8_t *const messages[4], size_t len,
                  uint8_t digests[4][SM3_DIGEST_SIZE]) {
    uint32x4_t state[8] = {
        vdupq_n_u32(SM3_IV0), vdupq_n_u32(SM3_IV1),
        vdupq_n_u32(SM3_IV2), vdupq_n_u32(SM3_IV3),
        vdupq_n_u32(SM3_IV4), vdupq_n_u32(SM3_IV5),
        vdupq_n_u32(SM3_IV6), vdupq_n_u32(SM3_IV7)
    };

    const size_t full = len / 64U;
    for (size_t block = 0; block < full; ++block) {
        const uint8_t *ptrs[4];
        for (unsigned lane = 0; lane < 4; ++lane) {
            ptrs[lane] = messages[lane] + block * 64U;
        }
        compress4(state, ptrs);
    }

    uint8_t tail[4][128];
    unsigned tail_blocks = 0;
    for (unsigned lane = 0; lane < 4; ++lane) {
        const unsigned n = sm3_prepare_tail(messages[lane], len, tail[lane]);
        if (lane == 0U) {
            tail_blocks = n;
        }
    }
    for (unsigned block = 0; block < tail_blocks; ++block) {
        const uint8_t *ptrs[4];
        for (unsigned lane = 0; lane < 4; ++lane) {
            ptrs[lane] = tail[lane] + 64U * block;
        }
        compress4(state, ptrs);
    }

    uint32_t lanes[4];
    for (unsigned word = 0; word < 8; ++word) {
        vst1q_u32(lanes, state[word]);
        for (unsigned lane = 0; lane < 4; ++lane) {
            sm3_store_be32(digests[lane] + 4U * word, lanes[lane]);
        }
    }
}
