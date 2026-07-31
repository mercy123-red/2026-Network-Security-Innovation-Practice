#ifndef GIFT64_H
#define GIFT64_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GIFT64_BLOCK_SIZE 8
#define GIFT64_KEY_SIZE 16
#define GIFT64_ROUNDS 28

typedef struct {
    uint8_t round_keys[GIFT64_ROUNDS][32]; /* 128-bit key as 32 nibbles, LSB nibble first */
    uint64_t round_masks[GIFT64_ROUNDS];
} gift64_ctx;

int gift64_init(gift64_ctx *ctx, const uint8_t key[GIFT64_KEY_SIZE]);
void gift64_encrypt_basic(const gift64_ctx *ctx, const uint8_t in[8], uint8_t out[8]);
void gift64_decrypt_basic(const gift64_ctx *ctx, const uint8_t in[8], uint8_t out[8]);
void gift64_encrypt_ttable(const gift64_ctx *ctx, const uint8_t in[8], uint8_t out[8]);
void gift64_encrypt8_avx2(const gift64_ctx *ctx, const uint8_t in[64], uint8_t out[64]);

#ifdef __cplusplus
}
#endif

#endif
