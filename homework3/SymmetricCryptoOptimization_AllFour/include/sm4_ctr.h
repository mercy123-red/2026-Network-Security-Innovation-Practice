#ifndef SYMOPT_SM4_CTR_H
#define SYMOPT_SM4_CTR_H

#include <stddef.h>
#include <stdint.h>
#include "sm4.h"

#ifdef __cplusplus
extern "C" {
#endif

void sm4_ctr_crypt_basic(const sm4_ctx *ctx,
                         const uint8_t initial_counter[16],
                         const uint8_t *in, uint8_t *out, size_t len);
void sm4_ctr_crypt_ttable(const sm4_ctx *ctx,
                          const uint8_t initial_counter[16],
                          const uint8_t *in, uint8_t *out, size_t len);
void sm4_ctr_crypt_avx2(const sm4_ctx *ctx,
                        const uint8_t initial_counter[16],
                        const uint8_t *in, uint8_t *out, size_t len);

#ifdef __cplusplus
}
#endif

#endif
