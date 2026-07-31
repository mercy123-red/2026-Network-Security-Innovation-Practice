#ifndef SYMOPT_SM4_INTERNAL_H
#define SYMOPT_SM4_INTERNAL_H

#include <stdint.h>
#include "sm4.h"

extern const uint8_t SM4_SBOX[256];
extern uint32_t SM4_T0[256];
extern uint32_t SM4_T1[256];
extern uint32_t SM4_T2[256];
extern uint32_t SM4_T3[256];

static inline uint32_t sm4_rotl32(uint32_t x, unsigned n) {
    return (x << n) | (x >> (32U - n));
}

static inline uint32_t sm4_load_be32(const uint8_t *p) {
    return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
           ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}

static inline void sm4_store_be32(uint8_t *p, uint32_t x) {
    p[0] = (uint8_t)(x >> 24);
    p[1] = (uint8_t)(x >> 16);
    p[2] = (uint8_t)(x >> 8);
    p[3] = (uint8_t)x;
}

uint32_t sm4_tau(uint32_t x);
uint32_t sm4_t(uint32_t x);
uint32_t sm4_t_key(uint32_t x);
void sm4_init_ttables(void);
uint32_t sm4_ttable_transform(uint32_t x);

#endif
