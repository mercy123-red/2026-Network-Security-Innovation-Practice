#include "sm4_internal.h"

uint32_t SM4_T0[256];
uint32_t SM4_T1[256];
uint32_t SM4_T2[256];
uint32_t SM4_T3[256];
static int ready = 0;

static uint32_t linear(uint32_t b) {
    return b ^ sm4_rotl32(b,2) ^ sm4_rotl32(b,10) ^
           sm4_rotl32(b,18) ^ sm4_rotl32(b,24);
}

void sm4_init_ttables(void) {
    if (ready) {
        return;
    }
    for (unsigned x = 0; x < 256; ++x) {
        SM4_T0[x] = linear((uint32_t)SM4_SBOX[x] << 24);
        SM4_T1[x] = linear((uint32_t)SM4_SBOX[x] << 16);
        SM4_T2[x] = linear((uint32_t)SM4_SBOX[x] << 8);
        SM4_T3[x] = linear((uint32_t)SM4_SBOX[x]);
    }
    ready = 1;
}

uint32_t sm4_ttable_transform(uint32_t x) {
    return SM4_T0[(x >> 24) & 0xffU] ^
           SM4_T1[(x >> 16) & 0xffU] ^
           SM4_T2[(x >> 8) & 0xffU] ^
           SM4_T3[x & 0xffU];
}

static void sm4_crypt_ttable_rk(const uint32_t rk[32],
                                const uint8_t in[16], uint8_t out[16]) {
    uint32_t x0 = sm4_load_be32(in);
    uint32_t x1 = sm4_load_be32(in + 4);
    uint32_t x2 = sm4_load_be32(in + 8);
    uint32_t x3 = sm4_load_be32(in + 12);

    for (unsigned i = 0; i < 32; ++i) {
        const uint32_t n = x0 ^ sm4_ttable_transform(x1 ^ x2 ^ x3 ^ rk[i]);
        x0=x1; x1=x2; x2=x3; x3=n;
    }
    sm4_store_be32(out, x3);
    sm4_store_be32(out + 4, x2);
    sm4_store_be32(out + 8, x1);
    sm4_store_be32(out + 12, x0);
}

void sm4_encrypt_ttable(const sm4_ctx *ctx,
                        const uint8_t in[16], uint8_t out[16]) {
    sm4_crypt_ttable_rk(ctx->rk_enc, in, out);
}

void sm4_decrypt_ttable(const sm4_ctx *ctx,
                        const uint8_t in[16], uint8_t out[16]) {
    sm4_crypt_ttable_rk(ctx->rk_dec, in, out);
}
