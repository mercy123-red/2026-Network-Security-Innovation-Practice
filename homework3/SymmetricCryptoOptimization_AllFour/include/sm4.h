#ifndef SYMOPT_SM4_H
#define SYMOPT_SM4_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SM4_BLOCK_SIZE 16
#define SM4_ROUNDS 32

typedef struct {
    uint32_t rk_enc[SM4_ROUNDS];
    uint32_t rk_dec[SM4_ROUNDS];
} sm4_ctx;

int sm4_init(sm4_ctx *ctx, const uint8_t key[16]);

void sm4_encrypt_basic(const sm4_ctx *ctx,
                       const uint8_t in[16], uint8_t out[16]);
void sm4_decrypt_basic(const sm4_ctx *ctx,
                       const uint8_t in[16], uint8_t out[16]);

void sm4_encrypt_ttable(const sm4_ctx *ctx,
                        const uint8_t in[16], uint8_t out[16]);
void sm4_decrypt_ttable(const sm4_ctx *ctx,
                        const uint8_t in[16], uint8_t out[16]);

void sm4_encrypt8_avx2(const sm4_ctx *ctx,
                       const uint8_t in[8 * 16], uint8_t out[8 * 16]);
void sm4_decrypt8_avx2(const sm4_ctx *ctx,
                       const uint8_t in[8 * 16], uint8_t out[8 * 16]);

#ifdef __cplusplus
}
#endif

#endif
