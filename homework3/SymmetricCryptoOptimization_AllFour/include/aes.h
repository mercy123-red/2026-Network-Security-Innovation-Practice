#ifndef AES_OPT_AES_H
#define AES_OPT_AES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AES128_BLOCK_SIZE 16
#define AES128_ROUND_KEYS_SIZE 176

typedef struct {
    uint8_t round_keys[AES128_ROUND_KEYS_SIZE];
} aes128_ctx;

int aes128_init(aes128_ctx *ctx, const uint8_t key[16]);

void aes128_encrypt_basic(const aes128_ctx *ctx,
                          const uint8_t in[16], uint8_t out[16]);
void aes128_decrypt_basic(const aes128_ctx *ctx,
                          const uint8_t in[16], uint8_t out[16]);

void aes128_encrypt_ttable(const aes128_ctx *ctx,
                           const uint8_t in[16], uint8_t out[16]);
void aes128_decrypt_ttable(const aes128_ctx *ctx,
                           const uint8_t in[16], uint8_t out[16]);

void aes128_encrypt_shuffle(const aes128_ctx *ctx,
                            const uint8_t in[16], uint8_t out[16]);

void aes128_encrypt_aesni(const aes128_ctx *ctx,
                          const uint8_t in[16], uint8_t out[16]);
void aes128_decrypt_aesni(const aes128_ctx *ctx,
                          const uint8_t in[16], uint8_t out[16]);

/* Process exactly eight independent 16-byte blocks. */
void aes128_encrypt8_vaes(const aes128_ctx *ctx,
                          const uint8_t in[8 * 16], uint8_t out[8 * 16]);
void aes128_decrypt8_vaes(const aes128_ctx *ctx,
                          const uint8_t in[8 * 16], uint8_t out[8 * 16]);

#ifdef __cplusplus
}
#endif

#endif
