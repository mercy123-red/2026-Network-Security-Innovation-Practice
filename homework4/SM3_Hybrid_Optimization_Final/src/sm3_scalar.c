#include <string.h>
#include "sm3_internal.h"

void sm3_compress_scalar(uint32_t state[8], const uint8_t block[64]) {
    uint32_t w[68];
    uint32_t wp[64];

    for (unsigned j = 0; j < 16; ++j) {
        w[j] = sm3_load_be32(block + 4U * j);
    }
    for (unsigned j = 16; j < 68; ++j) {
        const uint32_t x = w[j - 16] ^ w[j - 9] ^ sm3_rotl32(w[j - 3], 15);
        w[j] = sm3_p1(x) ^ sm3_rotl32(w[j - 13], 7) ^ w[j - 6];
    }
    for (unsigned j = 0; j < 64; ++j) {
        wp[j] = w[j] ^ w[j + 4];
    }

    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];
    uint32_t e = state[4];
    uint32_t f = state[5];
    uint32_t g = state[6];
    uint32_t h = state[7];

    for (unsigned j = 0; j < 64; ++j) {
        const uint32_t tj = j < 16U ? UINT32_C(0x79cc4519) : UINT32_C(0x7a879d8a);
        const uint32_t a12 = sm3_rotl32(a, 12);
        const uint32_t ss1 = sm3_rotl32(a12 + e + sm3_rotl32(tj, j), 7);
        const uint32_t ss2 = ss1 ^ a12;
        const uint32_t ff = j < 16U ? (a ^ b ^ c)
                                    : ((a & b) | (a & c) | (b & c));
        const uint32_t gg = j < 16U ? (e ^ f ^ g)
                                    : ((e & f) | ((~e) & g));
        const uint32_t tt1 = ff + d + ss2 + wp[j];
        const uint32_t tt2 = gg + h + ss1 + w[j];

        d = c;
        c = sm3_rotl32(b, 9);
        b = a;
        a = tt1;
        h = g;
        g = sm3_rotl32(f, 19);
        f = e;
        e = sm3_p0(tt2);
    }

    state[0] ^= a;
    state[1] ^= b;
    state[2] ^= c;
    state[3] ^= d;
    state[4] ^= e;
    state[5] ^= f;
    state[6] ^= g;
    state[7] ^= h;
}

void sm3_init(sm3_ctx *ctx) {
    if (ctx == NULL) {
        return;
    }
    ctx->state[0] = SM3_IV0;
    ctx->state[1] = SM3_IV1;
    ctx->state[2] = SM3_IV2;
    ctx->state[3] = SM3_IV3;
    ctx->state[4] = SM3_IV4;
    ctx->state[5] = SM3_IV5;
    ctx->state[6] = SM3_IV6;
    ctx->state[7] = SM3_IV7;
    ctx->total_len = 0;
    ctx->buffer_len = 0;
}

void sm3_update(sm3_ctx *ctx, const void *data, size_t len) {
    if (ctx == NULL || (data == NULL && len != 0U)) {
        return;
    }

    const uint8_t *input = (const uint8_t *)data;
    ctx->total_len += (uint64_t)len;

    if (ctx->buffer_len != 0U) {
        const size_t need = SM3_BLOCK_SIZE - ctx->buffer_len;
        const size_t take = len < need ? len : need;
        memcpy(ctx->buffer + ctx->buffer_len, input, take);
        ctx->buffer_len += take;
        input += take;
        len -= take;
        if (ctx->buffer_len == SM3_BLOCK_SIZE) {
            sm3_compress_scalar(ctx->state, ctx->buffer);
            ctx->buffer_len = 0;
        }
    }

    while (len >= SM3_BLOCK_SIZE) {
        sm3_compress_scalar(ctx->state, input);
        input += SM3_BLOCK_SIZE;
        len -= SM3_BLOCK_SIZE;
    }

    if (len != 0U) {
        memcpy(ctx->buffer, input, len);
        ctx->buffer_len = len;
    }
}

void sm3_final(sm3_ctx *ctx, uint8_t digest[SM3_DIGEST_SIZE]) {
    if (ctx == NULL || digest == NULL) {
        return;
    }

    uint8_t tail[128];
    const size_t rem = ctx->buffer_len;
    const unsigned blocks = rem <= 55U ? 1U : 2U;
    const size_t total = (size_t)blocks * SM3_BLOCK_SIZE;

    memset(tail, 0, total);
    memcpy(tail, ctx->buffer, rem);
    tail[rem] = 0x80U;
    sm3_store_be64(tail + total - 8U, ctx->total_len * UINT64_C(8));

    sm3_compress_scalar(ctx->state, tail);
    if (blocks == 2U) {
        sm3_compress_scalar(ctx->state, tail + 64);
    }

    for (unsigned i = 0; i < 8; ++i) {
        sm3_store_be32(digest + 4U * i, ctx->state[i]);
    }

    memset(ctx, 0, sizeof(*ctx));
}

void sm3_hash(const void *data, size_t len, uint8_t digest[SM3_DIGEST_SIZE]) {
    sm3_ctx ctx;
    sm3_init(&ctx);
    sm3_update(&ctx, data, len);
    sm3_final(&ctx, digest);
}
