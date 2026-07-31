#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "gift64.h"

static const uint8_t GIFT_S[16] = {
    0x1,0xa,0x4,0xc,0x6,0xf,0x3,0x9,0x2,0xd,0xb,0x7,0x5,0x0,0x8,0xe
};
static const uint8_t GIFT_S_INV[16] = {
    0xd,0x0,0x8,0x6,0x2,0xc,0x4,0xb,0xe,0x7,0x1,0xa,0x3,0x9,0xf,0x5
};
static const uint8_t GIFT_P[64] = {
     0,17,34,51,48, 1,18,35,32,49, 2,19,16,33,50, 3,
     4,21,38,55,52, 5,22,39,36,53, 6,23,20,37,54, 7,
     8,25,42,59,56, 9,26,43,40,57,10,27,24,41,58,11,
    12,29,46,63,60,13,30,47,44,61,14,31,28,45,62,15
};
static const uint8_t GIFT_P_INV[64] = {
     0, 5,10,15,16,21,26,31,32,37,42,47,48,53,58,63,
    12, 1, 6,11,28,17,22,27,44,33,38,43,60,49,54,59,
     8,13, 2, 7,24,29,18,23,40,45,34,39,56,61,50,55,
     4, 9,14, 3,20,25,30,19,36,41,46,35,52,57,62,51
};
static const uint8_t GIFT_RC[GIFT64_ROUNDS] = {
    0x01,0x03,0x07,0x0f,0x1f,0x3e,0x3d,0x3b,0x37,0x2f,
    0x1e,0x3c,0x39,0x33,0x27,0x0e,0x1d,0x3a,0x35,0x2b,
    0x16,0x2c,0x18,0x30,0x21,0x02,0x05,0x0b
};

static uint64_t SP_TABLE[16][16];
static int sp_ready;

static uint64_t load_be64(const uint8_t p[8]) {
    uint64_t x = 0;
    for (unsigned i = 0; i < 8; ++i) x = (x << 8) | p[i];
    return x;
}
static void store_be64(uint8_t p[8], uint64_t x) {
    for (int i = 7; i >= 0; --i) { p[i] = (uint8_t)x; x >>= 8; }
}

static void key_bytes_to_nibbles(const uint8_t key[16], uint8_t n[32]) {
    for (unsigned j = 0; j < 16; ++j) {
        n[31U - 2U*j] = (uint8_t)(key[j] >> 4);
        n[30U - 2U*j] = (uint8_t)(key[j] & 0x0fU);
    }
}

static void update_key(uint8_t key[32]) {
    uint8_t t[32];
    for (unsigned i = 0; i < 32; ++i) t[i] = key[(i + 8U) & 31U];
    for (unsigned i = 0; i < 24; ++i) key[i] = t[i];
    key[24] = t[27]; key[25] = t[24]; key[26] = t[25]; key[27] = t[26];
    key[28] = (uint8_t)(((t[28] & 0x0cU) >> 2) | ((t[29] & 0x03U) << 2));
    key[29] = (uint8_t)(((t[29] & 0x0cU) >> 2) | ((t[30] & 0x03U) << 2));
    key[30] = (uint8_t)(((t[30] & 0x0cU) >> 2) | ((t[31] & 0x03U) << 2));
    key[31] = (uint8_t)(((t[31] & 0x0cU) >> 2) | ((t[28] & 0x03U) << 2));
}

static uint64_t make_round_mask(const uint8_t key[32], unsigned round) {
    uint64_t mask = 0;
    for (unsigned i = 0; i < 16; ++i) {
        const unsigned b0 = i;
        const unsigned b1 = i + 16U;
        const unsigned v0 = (key[b0 / 4U] >> (b0 & 3U)) & 1U;
        const unsigned v1 = (key[b1 / 4U] >> (b1 & 3U)) & 1U;
        mask ^= (uint64_t)v0 << (4U*i);
        mask ^= (uint64_t)v1 << (4U*i + 1U);
    }
    for (unsigned b = 0; b < 6; ++b)
        mask ^= (uint64_t)((GIFT_RC[round] >> b) & 1U) << (3U + 4U*b);
    mask ^= UINT64_C(1) << 63;
    return mask;
}

static void init_sp_table(void) {
    if (sp_ready) return;
    for (unsigned pos = 0; pos < 16; ++pos) {
        for (unsigned x = 0; x < 16; ++x) {
            uint64_t y = 0;
            const uint8_t s = GIFT_S[x];
            for (unsigned b = 0; b < 4; ++b)
                y |= (uint64_t)((s >> b) & 1U) << GIFT_P[4U*pos + b];
            SP_TABLE[pos][x] = y;
        }
    }
    sp_ready = 1;
}

int gift64_init(gift64_ctx *ctx, const uint8_t key[16]) {
    uint8_t k[32];
    if (!ctx || !key) return -1;
    key_bytes_to_nibbles(key, k);
    for (unsigned r = 0; r < GIFT64_ROUNDS; ++r) {
        memcpy(ctx->round_keys[r], k, sizeof(k));
        ctx->round_masks[r] = make_round_mask(k, r);
        update_key(k);
    }
    init_sp_table();
    return 0;
}

static uint64_t sub_cells(uint64_t s, const uint8_t box[16]) {
    uint64_t y = 0;
    for (unsigned i = 0; i < 16; ++i)
        y |= (uint64_t)box[(s >> (4U*i)) & 0x0fU] << (4U*i);
    return y;
}
static uint64_t perm_bits(uint64_t s, const uint8_t p[64]) {
    uint64_t y = 0;
    for (unsigned i = 0; i < 64; ++i) y |= ((s >> i) & 1U) << p[i];
    return y;
}

void gift64_encrypt_basic(const gift64_ctx *ctx, const uint8_t in[8], uint8_t out[8]) {
    uint64_t s = load_be64(in);
    for (unsigned r = 0; r < GIFT64_ROUNDS; ++r) {
        s = sub_cells(s, GIFT_S);
        s = perm_bits(s, GIFT_P);
        s ^= ctx->round_masks[r];
    }
    store_be64(out, s);
}

void gift64_decrypt_basic(const gift64_ctx *ctx, const uint8_t in[8], uint8_t out[8]) {
    uint64_t s = load_be64(in);
    for (int r = GIFT64_ROUNDS - 1; r >= 0; --r) {
        s ^= ctx->round_masks[r];
        s = perm_bits(s, GIFT_P_INV);
        s = sub_cells(s, GIFT_S_INV);
    }
    store_be64(out, s);
}

void gift64_encrypt_ttable(const gift64_ctx *ctx, const uint8_t in[8], uint8_t out[8]) {
    uint64_t s = load_be64(in);
    for (unsigned r = 0; r < GIFT64_ROUNDS; ++r) {
        uint64_t y = 0;
        for (unsigned i = 0; i < 16; ++i)
            y ^= SP_TABLE[i][(s >> (4U*i)) & 0x0fU];
        s = y ^ ctx->round_masks[r];
    }
    store_be64(out, s);
}

static __m256i gift_round4(__m256i s, uint64_t mask) {
    const __m256i nibble_mask = _mm256_set1_epi64x(0x0f);
    __m256i y = _mm256_setzero_si256();
    for (unsigned i = 0; i < 16; ++i) {
        __m256i idx = _mm256_and_si256(_mm256_srli_epi64(s, 4U*i), nibble_mask);
        __m256i v = _mm256_i64gather_epi64((const long long *)SP_TABLE[i], idx, 8);
        y = _mm256_xor_si256(y, v);
    }
    return _mm256_xor_si256(y, _mm256_set1_epi64x((long long)mask));
}

void gift64_encrypt8_avx2(const gift64_ctx *ctx, const uint8_t in[64], uint8_t out[64]) {
    uint64_t a[4], b[4];
    for (unsigned i = 0; i < 4; ++i) { a[i] = load_be64(in + 8U*i); b[i] = load_be64(in + 32U + 8U*i); }
    __m256i x0 = _mm256_loadu_si256((const __m256i *)a);
    __m256i x1 = _mm256_loadu_si256((const __m256i *)b);
    for (unsigned r = 0; r < GIFT64_ROUNDS; ++r) {
        x0 = gift_round4(x0, ctx->round_masks[r]);
        x1 = gift_round4(x1, ctx->round_masks[r]);
    }
    _mm256_storeu_si256((__m256i *)a, x0);
    _mm256_storeu_si256((__m256i *)b, x1);
    for (unsigned i = 0; i < 4; ++i) { store_be64(out + 8U*i, a[i]); store_be64(out + 32U + 8U*i, b[i]); }
}
