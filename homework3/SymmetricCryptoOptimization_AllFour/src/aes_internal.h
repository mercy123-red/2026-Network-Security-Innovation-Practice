#ifndef AES_OPT_INTERNAL_H
#define AES_OPT_INTERNAL_H

#include <stdint.h>
#include "aes.h"

extern const uint8_t AES_SBOX[256];
extern const uint8_t AES_INV_SBOX[256];

uint8_t aes_gmul(uint8_t a, uint8_t b);
void aes_add_round_key(uint8_t state[16], const uint8_t rk[16]);
void aes_sub_bytes(uint8_t state[16]);
void aes_inv_sub_bytes(uint8_t state[16]);
void aes_shift_rows(uint8_t state[16]);
void aes_inv_shift_rows(uint8_t state[16]);
void aes_mix_columns(uint8_t state[16]);
void aes_inv_mix_columns(uint8_t state[16]);

static inline uint32_t aes_load_be32(const uint8_t *p) {
    return ((uint32_t)p[0] << 24) |
           ((uint32_t)p[1] << 16) |
           ((uint32_t)p[2] << 8) |
           (uint32_t)p[3];
}

static inline void aes_store_be32(uint8_t *p, uint32_t x) {
    p[0] = (uint8_t)(x >> 24);
    p[1] = (uint8_t)(x >> 16);
    p[2] = (uint8_t)(x >> 8);
    p[3] = (uint8_t)x;
}

static inline uint32_t aes_rotr32(uint32_t x, unsigned n) {
    return (x >> n) | (x << (32U - n));
}

#endif
