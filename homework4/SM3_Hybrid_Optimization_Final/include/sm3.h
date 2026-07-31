#ifndef SM3_HYBRID_SM3_H
#define SM3_HYBRID_SM3_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SM3_BLOCK_SIZE 64U
#define SM3_DIGEST_SIZE 32U

typedef struct {
    uint32_t state[8];
    uint64_t total_len;
    uint8_t buffer[SM3_BLOCK_SIZE];
    size_t buffer_len;
} sm3_ctx;

typedef enum {
    SM3_BACKEND_AUTO = 0,
    SM3_BACKEND_SCALAR,
    SM3_BACKEND_AVX2,
    SM3_BACKEND_AVX512,
    SM3_BACKEND_NEON
} sm3_backend;

void sm3_init(sm3_ctx *ctx);
void sm3_update(sm3_ctx *ctx, const void *data, size_t len);
void sm3_final(sm3_ctx *ctx, uint8_t digest[SM3_DIGEST_SIZE]);
void sm3_hash(const void *data, size_t len, uint8_t digest[SM3_DIGEST_SIZE]);

/*
 * Hash count independent messages that all have the same length.
 * digests is count * SM3_DIGEST_SIZE bytes in message order.
 * Returns 0 on success, -1 for invalid arguments, -2 if an explicitly
 * requested backend is unavailable on the current CPU/build.
 */
int sm3_hash_many_equal(const uint8_t *const *messages,
                        size_t count,
                        size_t len,
                        uint8_t *digests,
                        sm3_backend backend);

int sm3_backend_available(sm3_backend backend);
const char *sm3_backend_name(sm3_backend backend);
sm3_backend sm3_best_backend(void);

/* Architecture-specific fixed-width multi-buffer entry points. */
#if defined(SM3_HAVE_AVX2)
void sm3_mb8_avx2(const uint8_t *const messages[8], size_t len,
                  uint8_t digests[8][SM3_DIGEST_SIZE]);
#endif

#if defined(SM3_HAVE_AVX512)
void sm3_mb16_avx512(const uint8_t *const messages[16], size_t len,
                     uint8_t digests[16][SM3_DIGEST_SIZE]);
#endif

#if defined(SM3_HAVE_NEON)
void sm3_mb4_neon(const uint8_t *const messages[4], size_t len,
                  uint8_t digests[4][SM3_DIGEST_SIZE]);
#endif

#ifdef __cplusplus
}
#endif

#endif
