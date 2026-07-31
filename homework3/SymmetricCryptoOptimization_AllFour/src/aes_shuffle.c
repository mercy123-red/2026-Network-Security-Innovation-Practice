#include <immintrin.h>
#include <stdint.h>
#include "aes_internal.h"

/*
 * "Shuffle" implementation:
 * - SubBytes remains an explicit software S-box lookup.
 * - ShiftRows uses SSSE3 VPSHUFB/PSHUFB.
 * - MixColumns is computed in parallel across all 16 bytes.
 *
 * This is intentionally a distinct software-SIMD method from AES-NI/VAES.
 */

static inline __m128i xtime_bytes(__m128i x) {
    const __m128i fe = _mm_set1_epi8((char)0xfe);
    const __m128i poly = _mm_set1_epi8(0x1b);
    const __m128i zero = _mm_setzero_si128();
    const __m128i shifted = _mm_and_si128(_mm_slli_epi16(x, 1), fe);
    const __m128i high = _mm_cmplt_epi8(x, zero);
    return _mm_xor_si128(shifted, _mm_and_si128(high, poly));
}

static inline __m128i mix_columns_vec(__m128i s) {
    const __m128i rot1 = _mm_setr_epi8(
        1,2,3,0, 5,6,7,4, 9,10,11,8, 13,14,15,12);
    const __m128i rot2 = _mm_setr_epi8(
        2,3,0,1, 6,7,4,5, 10,11,8,9, 14,15,12,13);
    const __m128i rot3 = _mm_setr_epi8(
        3,0,1,2, 7,4,5,6, 11,8,9,10, 15,12,13,14);

    const __m128i r1 = _mm_shuffle_epi8(s, rot1);
    const __m128i r2 = _mm_shuffle_epi8(s, rot2);
    const __m128i r3 = _mm_shuffle_epi8(s, rot3);

    return _mm_xor_si128(
        _mm_xor_si128(xtime_bytes(s), xtime_bytes(r1)),
        _mm_xor_si128(r1, _mm_xor_si128(r2, r3)));
}

void aes128_encrypt_shuffle(const aes128_ctx *ctx,
                            const uint8_t in[16], uint8_t out[16]) {
    const __m128i shift_rows = _mm_setr_epi8(
        0,5,10,15, 4,9,14,3, 8,13,2,7, 12,1,6,11);
    uint8_t bytes[16];

    __m128i state = _mm_loadu_si128((const __m128i *)in);
    state = _mm_xor_si128(
        state, _mm_loadu_si128((const __m128i *)ctx->round_keys));

    for (unsigned round = 1; round < 10; ++round) {
        _mm_storeu_si128((__m128i *)bytes, state);
        for (unsigned i = 0; i < 16; ++i) {
            bytes[i] = AES_SBOX[bytes[i]];
        }
        state = _mm_loadu_si128((const __m128i *)bytes);
        state = _mm_shuffle_epi8(state, shift_rows);
        state = mix_columns_vec(state);
        state = _mm_xor_si128(
            state,
            _mm_loadu_si128((const __m128i *)(ctx->round_keys + 16*round)));
    }

    _mm_storeu_si128((__m128i *)bytes, state);
    for (unsigned i = 0; i < 16; ++i) {
        bytes[i] = AES_SBOX[bytes[i]];
    }
    state = _mm_loadu_si128((const __m128i *)bytes);
    state = _mm_shuffle_epi8(state, shift_rows);
    state = _mm_xor_si128(
        state, _mm_loadu_si128((const __m128i *)(ctx->round_keys + 160)));
    _mm_storeu_si128((__m128i *)out, state);
}
