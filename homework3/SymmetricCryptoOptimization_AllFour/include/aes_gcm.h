#ifndef AES_OPT_GCM_H
#define AES_OPT_GCM_H

#include <stddef.h>
#include <stdint.h>
#include "aes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AES_GCM_TAG_SIZE 16

typedef struct {
    aes128_ctx aes;
    uint8_t hash_subkey[16];
} aes128_gcm_ctx;

int aes128_gcm_init(aes128_gcm_ctx *ctx, const uint8_t key[16]);

/* Reference software implementation: basic AES plus bit-serial GHASH. */
int aes128_gcm_encrypt_basic(const aes128_gcm_ctx *ctx,
                             const uint8_t *iv, size_t iv_len,
                             const uint8_t *aad, size_t aad_len,
                             const uint8_t *plaintext, uint8_t *ciphertext,
                             size_t text_len, uint8_t tag[16]);

int aes128_gcm_decrypt_basic(const aes128_gcm_ctx *ctx,
                             const uint8_t *iv, size_t iv_len,
                             const uint8_t *aad, size_t aad_len,
                             const uint8_t *ciphertext, uint8_t *plaintext,
                             size_t text_len, const uint8_t tag[16]);

/* AES-NI counter mode plus PCLMULQDQ GHASH. */
int aes128_gcm_encrypt_aesni_pclmul(const aes128_gcm_ctx *ctx,
                                    const uint8_t *iv, size_t iv_len,
                                    const uint8_t *aad, size_t aad_len,
                                    const uint8_t *plaintext,
                                    uint8_t *ciphertext, size_t text_len,
                                    uint8_t tag[16]);

int aes128_gcm_decrypt_aesni_pclmul(const aes128_gcm_ctx *ctx,
                                    const uint8_t *iv, size_t iv_len,
                                    const uint8_t *aad, size_t aad_len,
                                    const uint8_t *ciphertext,
                                    uint8_t *plaintext, size_t text_len,
                                    const uint8_t tag[16]);

/* Eight-block VAES CTR path plus PCLMULQDQ GHASH. */
int aes128_gcm_encrypt_vaes8_pclmul(const aes128_gcm_ctx *ctx,
                                    const uint8_t *iv, size_t iv_len,
                                    const uint8_t *aad, size_t aad_len,
                                    const uint8_t *plaintext,
                                    uint8_t *ciphertext, size_t text_len,
                                    uint8_t tag[16]);

int aes128_gcm_decrypt_vaes8_pclmul(const aes128_gcm_ctx *ctx,
                                    const uint8_t *iv, size_t iv_len,
                                    const uint8_t *aad, size_t aad_len,
                                    const uint8_t *ciphertext,
                                    uint8_t *plaintext, size_t text_len,
                                    const uint8_t tag[16]);

/* Exposed for correctness/performance experiments. */
void aes_gcm_ghash_basic(const uint8_t h[16],
                         const uint8_t *data, size_t len,
                         uint8_t accumulator[16]);
void aes_gcm_ghash_pclmul(const uint8_t h[16],
                          const uint8_t *data, size_t len,
                          uint8_t accumulator[16]);

#ifdef __cplusplus
}
#endif

#endif
