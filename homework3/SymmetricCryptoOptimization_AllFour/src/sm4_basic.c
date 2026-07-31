#include "sm4_internal.h"

static void sm4_crypt_basic_rk(const uint32_t rk[32],
                               const uint8_t in[16], uint8_t out[16]) {
    uint32_t x0 = sm4_load_be32(in);
    uint32_t x1 = sm4_load_be32(in + 4);
    uint32_t x2 = sm4_load_be32(in + 8);
    uint32_t x3 = sm4_load_be32(in + 12);

    for (unsigned i = 0; i < 32; ++i) {
        const uint32_t n = x0 ^ sm4_t(x1 ^ x2 ^ x3 ^ rk[i]);
        x0=x1; x1=x2; x2=x3; x3=n;
    }
    sm4_store_be32(out, x3);
    sm4_store_be32(out + 4, x2);
    sm4_store_be32(out + 8, x1);
    sm4_store_be32(out + 12, x0);
}

void sm4_encrypt_basic(const sm4_ctx *ctx,
                       const uint8_t in[16], uint8_t out[16]) {
    sm4_crypt_basic_rk(ctx->rk_enc, in, out);
}

void sm4_decrypt_basic(const sm4_ctx *ctx,
                       const uint8_t in[16], uint8_t out[16]) {
    sm4_crypt_basic_rk(ctx->rk_dec, in, out);
}
