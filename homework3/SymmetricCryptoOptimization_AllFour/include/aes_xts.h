#ifndef AES_OPT_XTS_H
#define AES_OPT_XTS_H

#include <stddef.h>
#include <stdint.h>
#include "aes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    aes128_ctx data_key;
    aes128_ctx tweak_key;
} aes128_xts_ctx;

int aes128_xts_init(aes128_xts_ctx *ctx,
                    const uint8_t data_key[16],
                    const uint8_t tweak_key[16]);

/* len must be at least 16 bytes; ciphertext stealing handles a final partial block. */
int aes128_xts_encrypt_basic(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *plaintext,
                             uint8_t *ciphertext, size_t len);
int aes128_xts_decrypt_basic(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *ciphertext,
                             uint8_t *plaintext, size_t len);

int aes128_xts_encrypt_aesni(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *plaintext,
                             uint8_t *ciphertext, size_t len);
int aes128_xts_decrypt_aesni(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *ciphertext,
                             uint8_t *plaintext, size_t len);

int aes128_xts_encrypt_vaes8(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *plaintext,
                             uint8_t *ciphertext, size_t len);
int aes128_xts_decrypt_vaes8(const aes128_xts_ctx *ctx,
                             const uint8_t tweak_input[16],
                             const uint8_t *ciphertext,
                             uint8_t *plaintext, size_t len);

#ifdef __cplusplus
}
#endif

#endif
