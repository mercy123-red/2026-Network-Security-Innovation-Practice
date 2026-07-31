#include <stddef.h>
#include "aes_internal.h"

static uint32_t TE0[256], TE1[256], TE2[256], TE3[256];
static uint32_t TD0[256], TD1[256], TD2[256], TD3[256];
static int tables_ready = 0;

static void init_tables(void) {
    if (tables_ready) {
        return;
    }

    for (unsigned x = 0; x < 256; ++x) {
        const uint8_t s = AES_SBOX[x];
        const uint32_t te =
            ((uint32_t)aes_gmul(s,2) << 24) |
            ((uint32_t)s << 16) |
            ((uint32_t)s << 8) |
            (uint32_t)aes_gmul(s,3);
        TE0[x] = te;
        TE1[x] = aes_rotr32(te, 8);
        TE2[x] = aes_rotr32(te, 16);
        TE3[x] = aes_rotr32(te, 24);

        const uint8_t is = AES_INV_SBOX[x];
        const uint32_t td =
            ((uint32_t)aes_gmul(is,14) << 24) |
            ((uint32_t)aes_gmul(is,9) << 16) |
            ((uint32_t)aes_gmul(is,13) << 8) |
            (uint32_t)aes_gmul(is,11);
        TD0[x] = td;
        TD1[x] = aes_rotr32(td, 8);
        TD2[x] = aes_rotr32(td, 16);
        TD3[x] = aes_rotr32(td, 24);
    }
    tables_ready = 1;
}

static uint32_t inv_mcol_word(uint32_t x) {
    const uint8_t a0=(uint8_t)(x>>24), a1=(uint8_t)(x>>16);
    const uint8_t a2=(uint8_t)(x>>8),  a3=(uint8_t)x;
    return ((uint32_t)(aes_gmul(a0,14)^aes_gmul(a1,11)^aes_gmul(a2,13)^aes_gmul(a3,9))<<24) |
           ((uint32_t)(aes_gmul(a0,9)^aes_gmul(a1,14)^aes_gmul(a2,11)^aes_gmul(a3,13))<<16) |
           ((uint32_t)(aes_gmul(a0,13)^aes_gmul(a1,9)^aes_gmul(a2,14)^aes_gmul(a3,11))<<8) |
           ((uint32_t)(aes_gmul(a0,11)^aes_gmul(a1,13)^aes_gmul(a2,9)^aes_gmul(a3,14)));
}

void aes128_encrypt_ttable(const aes128_ctx *ctx,
                           const uint8_t in[16], uint8_t out[16]) {
    uint32_t rk[44];
    init_tables();

    for (unsigned i = 0; i < 44; ++i) {
        rk[i] = aes_load_be32(ctx->round_keys + 4*i);
    }

    uint32_t s0 = aes_load_be32(in)      ^ rk[0];
    uint32_t s1 = aes_load_be32(in + 4)  ^ rk[1];
    uint32_t s2 = aes_load_be32(in + 8)  ^ rk[2];
    uint32_t s3 = aes_load_be32(in + 12) ^ rk[3];

    unsigned rki = 4;
    for (unsigned round = 1; round < 10; ++round) {
        const uint32_t t0 =
            TE0[s0 >> 24] ^ TE1[(s1 >> 16) & 0xff] ^
            TE2[(s2 >> 8) & 0xff] ^ TE3[s3 & 0xff] ^ rk[rki++];
        const uint32_t t1 =
            TE0[s1 >> 24] ^ TE1[(s2 >> 16) & 0xff] ^
            TE2[(s3 >> 8) & 0xff] ^ TE3[s0 & 0xff] ^ rk[rki++];
        const uint32_t t2 =
            TE0[s2 >> 24] ^ TE1[(s3 >> 16) & 0xff] ^
            TE2[(s0 >> 8) & 0xff] ^ TE3[s1 & 0xff] ^ rk[rki++];
        const uint32_t t3 =
            TE0[s3 >> 24] ^ TE1[(s0 >> 16) & 0xff] ^
            TE2[(s1 >> 8) & 0xff] ^ TE3[s2 & 0xff] ^ rk[rki++];
        s0=t0; s1=t1; s2=t2; s3=t3;
    }

    const uint32_t t0 =
        ((uint32_t)AES_SBOX[s0 >> 24] << 24) |
        ((uint32_t)AES_SBOX[(s1 >> 16) & 0xff] << 16) |
        ((uint32_t)AES_SBOX[(s2 >> 8) & 0xff] << 8) |
        (uint32_t)AES_SBOX[s3 & 0xff];
    const uint32_t t1 =
        ((uint32_t)AES_SBOX[s1 >> 24] << 24) |
        ((uint32_t)AES_SBOX[(s2 >> 16) & 0xff] << 16) |
        ((uint32_t)AES_SBOX[(s3 >> 8) & 0xff] << 8) |
        (uint32_t)AES_SBOX[s0 & 0xff];
    const uint32_t t2 =
        ((uint32_t)AES_SBOX[s2 >> 24] << 24) |
        ((uint32_t)AES_SBOX[(s3 >> 16) & 0xff] << 16) |
        ((uint32_t)AES_SBOX[(s0 >> 8) & 0xff] << 8) |
        (uint32_t)AES_SBOX[s1 & 0xff];
    const uint32_t t3 =
        ((uint32_t)AES_SBOX[s3 >> 24] << 24) |
        ((uint32_t)AES_SBOX[(s0 >> 16) & 0xff] << 16) |
        ((uint32_t)AES_SBOX[(s1 >> 8) & 0xff] << 8) |
        (uint32_t)AES_SBOX[s2 & 0xff];

    aes_store_be32(out,      t0 ^ rk[40]);
    aes_store_be32(out + 4,  t1 ^ rk[41]);
    aes_store_be32(out + 8,  t2 ^ rk[42]);
    aes_store_be32(out + 12, t3 ^ rk[43]);
}

void aes128_decrypt_ttable(const aes128_ctx *ctx,
                           const uint8_t in[16], uint8_t out[16]) {
    uint32_t erk[44], drk[44];
    init_tables();

    for (unsigned i = 0; i < 44; ++i) {
        erk[i] = aes_load_be32(ctx->round_keys + 4*i);
    }

    for (unsigned i = 0; i < 4; ++i) {
        drk[i] = erk[40+i];
        drk[40+i] = erk[i];
    }
    for (unsigned round = 1; round < 10; ++round) {
        for (unsigned i = 0; i < 4; ++i) {
            drk[4*round+i] = inv_mcol_word(erk[40-4*round+i]);
        }
    }

    uint32_t s0 = aes_load_be32(in)      ^ drk[0];
    uint32_t s1 = aes_load_be32(in + 4)  ^ drk[1];
    uint32_t s2 = aes_load_be32(in + 8)  ^ drk[2];
    uint32_t s3 = aes_load_be32(in + 12) ^ drk[3];

    unsigned rki = 4;
    for (unsigned round = 1; round < 10; ++round) {
        const uint32_t t0 =
            TD0[s0 >> 24] ^ TD1[(s3 >> 16) & 0xff] ^
            TD2[(s2 >> 8) & 0xff] ^ TD3[s1 & 0xff] ^ drk[rki++];
        const uint32_t t1 =
            TD0[s1 >> 24] ^ TD1[(s0 >> 16) & 0xff] ^
            TD2[(s3 >> 8) & 0xff] ^ TD3[s2 & 0xff] ^ drk[rki++];
        const uint32_t t2 =
            TD0[s2 >> 24] ^ TD1[(s1 >> 16) & 0xff] ^
            TD2[(s0 >> 8) & 0xff] ^ TD3[s3 & 0xff] ^ drk[rki++];
        const uint32_t t3 =
            TD0[s3 >> 24] ^ TD1[(s2 >> 16) & 0xff] ^
            TD2[(s1 >> 8) & 0xff] ^ TD3[s0 & 0xff] ^ drk[rki++];
        s0=t0; s1=t1; s2=t2; s3=t3;
    }

    const uint32_t t0 =
        ((uint32_t)AES_INV_SBOX[s0 >> 24] << 24) |
        ((uint32_t)AES_INV_SBOX[(s3 >> 16) & 0xff] << 16) |
        ((uint32_t)AES_INV_SBOX[(s2 >> 8) & 0xff] << 8) |
        (uint32_t)AES_INV_SBOX[s1 & 0xff];
    const uint32_t t1 =
        ((uint32_t)AES_INV_SBOX[s1 >> 24] << 24) |
        ((uint32_t)AES_INV_SBOX[(s0 >> 16) & 0xff] << 16) |
        ((uint32_t)AES_INV_SBOX[(s3 >> 8) & 0xff] << 8) |
        (uint32_t)AES_INV_SBOX[s2 & 0xff];
    const uint32_t t2 =
        ((uint32_t)AES_INV_SBOX[s2 >> 24] << 24) |
        ((uint32_t)AES_INV_SBOX[(s1 >> 16) & 0xff] << 16) |
        ((uint32_t)AES_INV_SBOX[(s0 >> 8) & 0xff] << 8) |
        (uint32_t)AES_INV_SBOX[s3 & 0xff];
    const uint32_t t3 =
        ((uint32_t)AES_INV_SBOX[s3 >> 24] << 24) |
        ((uint32_t)AES_INV_SBOX[(s2 >> 16) & 0xff] << 16) |
        ((uint32_t)AES_INV_SBOX[(s1 >> 8) & 0xff] << 8) |
        (uint32_t)AES_INV_SBOX[s0 & 0xff];

    aes_store_be32(out,      t0 ^ drk[40]);
    aes_store_be32(out + 4,  t1 ^ drk[41]);
    aes_store_be32(out + 8,  t2 ^ drk[42]);
    aes_store_be32(out + 12, t3 ^ drk[43]);
}
