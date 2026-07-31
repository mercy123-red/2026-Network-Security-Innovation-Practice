#ifndef AES_OPT_CTR_H
#define AES_OPT_CTR_H

#include <stddef.h>
#include <stdint.h>
#include "aes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * AES-CTR encryption and decryption are the same operation.
 * The 128-bit initial counter is interpreted as a big-endian integer.
 * The input and output buffers may be identical.
 */
void aes128_ctr_crypt_basic(const aes128_ctx *ctx,
                            const uint8_t initial_counter[16],
                            const uint8_t *in, uint8_t *out, size_t len);

void aes128_ctr_crypt_ttable(const aes128_ctx *ctx,
                             const uint8_t initial_counter[16],
                             const uint8_t *in, uint8_t *out, size_t len);

void aes128_ctr_crypt_shuffle(const aes128_ctx *ctx,
                              const uint8_t initial_counter[16],
                              const uint8_t *in, uint8_t *out, size_t len);

void aes128_ctr_crypt_aesni(const aes128_ctx *ctx,
                            const uint8_t initial_counter[16],
                            const uint8_t *in, uint8_t *out, size_t len);

/* Processes eight counter blocks per loop with AVX2-width VAES. */
void aes128_ctr_crypt_vaes8(const aes128_ctx *ctx,
                            const uint8_t initial_counter[16],
                            const uint8_t *in, uint8_t *out, size_t len);

#ifdef __cplusplus
}
#endif

#endif
