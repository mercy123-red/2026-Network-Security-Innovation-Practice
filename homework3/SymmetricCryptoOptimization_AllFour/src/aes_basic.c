#include <string.h>
#include "aes_internal.h"

void aes128_encrypt_basic(const aes128_ctx *ctx,
                          const uint8_t in[16], uint8_t out[16]) {
    uint8_t state[16];
    memcpy(state, in, 16);

    aes_add_round_key(state, ctx->round_keys);
    for (unsigned round = 1; round < 10; ++round) {
        aes_sub_bytes(state);
        aes_shift_rows(state);
        aes_mix_columns(state);
        aes_add_round_key(state, ctx->round_keys + 16*round);
    }
    aes_sub_bytes(state);
    aes_shift_rows(state);
    aes_add_round_key(state, ctx->round_keys + 160);

    memcpy(out, state, 16);
}

void aes128_decrypt_basic(const aes128_ctx *ctx,
                          const uint8_t in[16], uint8_t out[16]) {
    uint8_t state[16];
    memcpy(state, in, 16);

    aes_add_round_key(state, ctx->round_keys + 160);
    for (int round = 9; round >= 1; --round) {
        aes_inv_shift_rows(state);
        aes_inv_sub_bytes(state);
        aes_add_round_key(state, ctx->round_keys + 16*round);
        aes_inv_mix_columns(state);
    }
    aes_inv_shift_rows(state);
    aes_inv_sub_bytes(state);
    aes_add_round_key(state, ctx->round_keys);

    memcpy(out, state, 16);
}
