#include <stddef.h>
#include <stdint.h>
#include "sm3.h"

#if defined(__x86_64__) || defined(__i386__)
static int cpu_has_avx2(void) {
#if defined(__GNUC__) || defined(__clang__)
    __builtin_cpu_init();
    return __builtin_cpu_supports("avx2") != 0;
#else
    return 0;
#endif
}

static int cpu_has_avx512f(void) {
#if defined(__GNUC__) || defined(__clang__)
    __builtin_cpu_init();
    return __builtin_cpu_supports("avx512f") != 0;
#else
    return 0;
#endif
}
#else
static int cpu_has_avx2(void) { return 0; }
static int cpu_has_avx512f(void) { return 0; }
#endif

int sm3_backend_available(sm3_backend backend) {
    switch (backend) {
        case SM3_BACKEND_AUTO:
        case SM3_BACKEND_SCALAR:
            return 1;
        case SM3_BACKEND_AVX2:
#if defined(SM3_HAVE_AVX2)
            return cpu_has_avx2();
#else
            return 0;
#endif
        case SM3_BACKEND_AVX512:
#if defined(SM3_HAVE_AVX512)
            return cpu_has_avx512f();
#else
            return 0;
#endif
        case SM3_BACKEND_NEON:
#if defined(SM3_HAVE_NEON)
            return 1;
#else
            return 0;
#endif
        default:
            return 0;
    }
}

const char *sm3_backend_name(sm3_backend backend) {
    switch (backend) {
        case SM3_BACKEND_AUTO: return "auto";
        case SM3_BACKEND_SCALAR: return "scalar-gpr";
        case SM3_BACKEND_AVX2: return "x86-avx2-hybrid";
        case SM3_BACKEND_AVX512: return "x86-avx512-hybrid";
        case SM3_BACKEND_NEON: return "arm64-neon-hybrid";
        default: return "unknown";
    }
}

sm3_backend sm3_best_backend(void) {
#if defined(SM3_HAVE_AVX512)
    if (cpu_has_avx512f()) {
        return SM3_BACKEND_AVX512;
    }
#endif
#if defined(SM3_HAVE_AVX2)
    if (cpu_has_avx2()) {
        return SM3_BACKEND_AVX2;
    }
#endif
#if defined(SM3_HAVE_NEON)
    return SM3_BACKEND_NEON;
#else
    return SM3_BACKEND_SCALAR;
#endif
}

static void hash_scalar_range(const uint8_t *const *messages,
                              size_t begin,
                              size_t end,
                              size_t len,
                              uint8_t *digests) {
    for (size_t i = begin; i < end; ++i) {
        sm3_hash(messages[i], len, digests + i * SM3_DIGEST_SIZE);
    }
}

int sm3_hash_many_equal(const uint8_t *const *messages,
                        size_t count,
                        size_t len,
                        uint8_t *digests,
                        sm3_backend backend) {
    if ((messages == NULL && count != 0U) ||
        (digests == NULL && count != 0U)) {
        return -1;
    }
    for (size_t i = 0; i < count; ++i) {
        if (messages[i] == NULL && len != 0U) {
            return -1;
        }
    }

    if (backend == SM3_BACKEND_AUTO) {
        backend = sm3_best_backend();
    } else if (!sm3_backend_available(backend)) {
        return -2;
    }

    size_t done = 0;

    if (backend == SM3_BACKEND_AVX512) {
#if defined(SM3_HAVE_AVX512)
        while (count - done >= 16U) {
            const uint8_t *batch[16];
            for (unsigned i = 0; i < 16; ++i) {
                batch[i] = messages[done + i];
            }
            sm3_mb16_avx512(batch, len,
                (uint8_t (*)[SM3_DIGEST_SIZE])(digests + done * SM3_DIGEST_SIZE));
            done += 16U;
        }
#endif
#if defined(SM3_HAVE_AVX2)
        if (cpu_has_avx2()) {
            while (count - done >= 8U) {
                const uint8_t *batch[8];
                for (unsigned i = 0; i < 8; ++i) {
                    batch[i] = messages[done + i];
                }
                sm3_mb8_avx2(batch, len,
                    (uint8_t (*)[SM3_DIGEST_SIZE])(digests + done * SM3_DIGEST_SIZE));
                done += 8U;
            }
        }
#endif
    } else if (backend == SM3_BACKEND_AVX2) {
#if defined(SM3_HAVE_AVX2)
        while (count - done >= 8U) {
            const uint8_t *batch[8];
            for (unsigned i = 0; i < 8; ++i) {
                batch[i] = messages[done + i];
            }
            sm3_mb8_avx2(batch, len,
                (uint8_t (*)[SM3_DIGEST_SIZE])(digests + done * SM3_DIGEST_SIZE));
            done += 8U;
        }
#endif
    } else if (backend == SM3_BACKEND_NEON) {
#if defined(SM3_HAVE_NEON)
        while (count - done >= 4U) {
            const uint8_t *batch[4];
            for (unsigned i = 0; i < 4; ++i) {
                batch[i] = messages[done + i];
            }
            sm3_mb4_neon(batch, len,
                (uint8_t (*)[SM3_DIGEST_SIZE])(digests + done * SM3_DIGEST_SIZE));
            done += 4U;
        }
#endif
    }

    hash_scalar_range(messages, done, count, len, digests);
    return 0;
}
