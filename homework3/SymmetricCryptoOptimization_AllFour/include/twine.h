#ifndef TWINE_H
#define TWINE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TWINE_BLOCK_SIZE 8
#define TWINE_ROUNDS 36

typedef struct {
    uint8_t round_keys[TWINE_ROUNDS][8];
} twine_ctx;

int twine80_init(twine_ctx *ctx, const uint8_t key[10]);
int twine128_init(twine_ctx *ctx, const uint8_t key[16]);
void twine_encrypt_basic(const twine_ctx *ctx, const uint8_t in[8], uint8_t out[8]);
void twine_decrypt_basic(const twine_ctx *ctx, const uint8_t in[8], uint8_t out[8]);
void twine_encrypt8_avx2(const twine_ctx *ctx, const uint8_t in[64], uint8_t out[64]);

#ifdef __cplusplus
}
#endif

#endif
