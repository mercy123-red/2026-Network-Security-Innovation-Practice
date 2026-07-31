#ifndef SM3_HYBRID_INTERNAL_H
#define SM3_HYBRID_INTERNAL_H

#include <stddef.h>
#include <stdint.h>
#include "sm3.h"

#define SM3_IV0 UINT32_C(0x7380166f)
#define SM3_IV1 UINT32_C(0x4914b2b9)
#define SM3_IV2 UINT32_C(0x172442d7)
#define SM3_IV3 UINT32_C(0xda8a0600)
#define SM3_IV4 UINT32_C(0xa96f30bc)
#define SM3_IV5 UINT32_C(0x163138aa)
#define SM3_IV6 UINT32_C(0xe38dee4d)
#define SM3_IV7 UINT32_C(0xb0fb0e4e)

static inline uint32_t sm3_rotl32(uint32_t x, unsigned n) {
    n &= 31U;
    return n == 0U ? x : (x << n) | (x >> (32U - n));
}

static inline uint32_t sm3_load_be32(const uint8_t *p) {
    return ((uint32_t)p[0] << 24) |
           ((uint32_t)p[1] << 16) |
           ((uint32_t)p[2] << 8) |
           (uint32_t)p[3];
}

static inline void sm3_store_be32(uint8_t *p, uint32_t x) {
    p[0] = (uint8_t)(x >> 24);
    p[1] = (uint8_t)(x >> 16);
    p[2] = (uint8_t)(x >> 8);
    p[3] = (uint8_t)x;
}

static inline void sm3_store_be64(uint8_t *p, uint64_t x) {
    p[0] = (uint8_t)(x >> 56);
    p[1] = (uint8_t)(x >> 48);
    p[2] = (uint8_t)(x >> 40);
    p[3] = (uint8_t)(x >> 32);
    p[4] = (uint8_t)(x >> 24);
    p[5] = (uint8_t)(x >> 16);
    p[6] = (uint8_t)(x >> 8);
    p[7] = (uint8_t)x;
}

static inline uint32_t sm3_p0(uint32_t x) {
    return x ^ sm3_rotl32(x, 9) ^ sm3_rotl32(x, 17);
}

static inline uint32_t sm3_p1(uint32_t x) {
    return x ^ sm3_rotl32(x, 15) ^ sm3_rotl32(x, 23);
}

void sm3_compress_scalar(uint32_t state[8], const uint8_t block[64]);

/* Prepare one or two final blocks without libc dependencies. */
static inline unsigned sm3_prepare_tail(const uint8_t *message,
                                        size_t len,
                                        uint8_t tail[128]) {
    const size_t rem = len & 63U;
    const size_t base = len - rem;
    const unsigned blocks = rem <= 55U ? 1U : 2U;
    const size_t total = (size_t)blocks * 64U;

    for (size_t i = 0; i < total; ++i) {
        tail[i] = 0;
    }
    for (size_t i = 0; i < rem; ++i) {
        tail[i] = message[base + i];
    }
    tail[rem] = 0x80U;
    sm3_store_be64(tail + total - 8U, (uint64_t)len * UINT64_C(8));
    return blocks;
}

#endif
