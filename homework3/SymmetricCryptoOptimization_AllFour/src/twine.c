#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "twine.h"

static const uint8_t S[16] = {0xc,0x0,0xf,0xa,0x2,0xb,0x9,0x5,0x8,0x3,0xd,0x7,0x1,0xe,0x6,0x4};
static const uint8_t PI[16] = {5,0,1,4,7,12,3,8,13,6,9,2,15,10,11,14};
static const uint8_t PI_INV[16] = {1,2,11,6,3,0,9,4,7,10,13,14,5,8,15,12};
static const uint8_t CON[36] = {
    0x01,0x02,0x04,0x08,0x10,0x20,0x03,0x06,0x0c,0x18,0x30,0x23,
    0x05,0x0a,0x14,0x28,0x13,0x26,0x0f,0x1e,0x3c,0x3b,0x35,0x29,
    0x11,0x22,0x07,0x0e,0x1c,0x38,0x33,0x25,0x09,0x12,0x24,0x0b
};

static void bytes_to_nibbles(const uint8_t *in, size_t bytes, uint8_t *n) {
    for (size_t i = 0; i < bytes; ++i) { n[2*i] = in[i] >> 4; n[2*i+1] = in[i] & 0x0f; }
}
static void nibbles_to_bytes(const uint8_t n[16], uint8_t out[8]) {
    for (unsigned i = 0; i < 8; ++i) out[i] = (uint8_t)((n[2*i] << 4) | n[2*i+1]);
}
static void extract80(const uint8_t w[20], uint8_t rk[8]) {
    static const uint8_t p[8] = {1,3,4,6,13,14,15,16};
    for (unsigned i=0;i<8;++i) rk[i]=w[p[i]];
}
static void extract128(const uint8_t w[32], uint8_t rk[8]) {
    static const uint8_t p[8] = {2,3,12,15,17,18,28,31};
    for (unsigned i=0;i<8;++i) rk[i]=w[p[i]];
}

int twine80_init(twine_ctx *ctx, const uint8_t key[10]) {
    uint8_t w[20];
    if (!ctx || !key) return -1;
    bytes_to_nibbles(key,10,w); extract80(w,ctx->round_keys[0]);
    for (unsigned r=1;r<TWINE_ROUNDS;++r) {
        const uint8_t c=CON[r-1];
        uint8_t old[20];
        w[1]^=S[w[0]]; w[4]^=S[w[16]]; w[7]^=(c>>3)&7U; w[19]^=c&7U;
        memcpy(old,w,sizeof(old));
        for (unsigned j=0;j<4;++j) memcpy(w+4*j,old+4*j+4,4);
        w[16]=old[1];w[17]=old[2];w[18]=old[3];w[19]=old[0];
        extract80(w,ctx->round_keys[r]);
    }
    return 0;
}

int twine128_init(twine_ctx *ctx, const uint8_t key[16]) {
    uint8_t w[32];
    if (!ctx || !key) return -1;
    bytes_to_nibbles(key,16,w); extract128(w,ctx->round_keys[0]);
    for (unsigned r=1;r<TWINE_ROUNDS;++r) {
        const uint8_t c=CON[r-1];
        uint8_t old[32];
        w[1]^=S[w[0]]; w[4]^=S[w[16]]; w[23]^=S[w[30]];
        w[7]^=(c>>3)&7U; w[19]^=c&7U;
        memcpy(old,w,sizeof(old));
        for (unsigned j=0;j<7;++j) memcpy(w+4*j,old+4*j+4,4);
        w[28]=old[1];w[29]=old[2];w[30]=old[3];w[31]=old[0];
        extract128(w,ctx->round_keys[r]);
    }
    return 0;
}

static void f_layer(uint8_t x[16], const uint8_t rk[8]) {
    for (unsigned j=0;j<8;++j) x[2*j+1]^=S[x[2*j]^rk[j]];
}
static void permute(uint8_t x[16], const uint8_t p[16]) {
    uint8_t t[16];
    for (unsigned h=0;h<16;++h) t[p[h]]=x[h];
    memcpy(x,t,16);
}

void twine_encrypt_basic(const twine_ctx *ctx, const uint8_t in[8], uint8_t out[8]) {
    uint8_t x[16]; bytes_to_nibbles(in,8,x);
    for (unsigned r=0;r<35;++r) { f_layer(x,ctx->round_keys[r]); permute(x,PI); }
    f_layer(x,ctx->round_keys[35]); nibbles_to_bytes(x,out);
}
void twine_decrypt_basic(const twine_ctx *ctx, const uint8_t in[8], uint8_t out[8]) {
    uint8_t x[16]; bytes_to_nibbles(in,8,x);
    for (int r=35;r>=1;--r) { f_layer(x,ctx->round_keys[r]); permute(x,PI_INV); }
    f_layer(x,ctx->round_keys[0]); nibbles_to_bytes(x,out);
}

static __m256i sbox_table(void) {
    return _mm256_setr_epi8(
        0xc,0x0,0xf,0xa,0x2,0xb,0x9,0x5,0x8,0x3,0xd,0x7,0x1,0xe,0x6,0x4,
        0xc,0x0,0xf,0xa,0x2,0xb,0x9,0x5,0x8,0x3,0xd,0x7,0x1,0xe,0x6,0x4);
}
static __m256i make_key_vec(const uint8_t rk[8]) {
    uint8_t k[32]={0};
    for (unsigned lane=0;lane<2;++lane) for (unsigned j=0;j<8;++j) k[16*lane+2*j]=rk[j];
    return _mm256_loadu_si256((const __m256i*)k);
}
static __m256i f_vec(__m256i x, const uint8_t rk[8]) {
    const __m256i tab=sbox_table();
    const __m256i mv=_mm256_setr_epi8(
        (char)0x80,0,(char)0x80,2,(char)0x80,4,(char)0x80,6,
        (char)0x80,8,(char)0x80,10,(char)0x80,12,(char)0x80,14,
        (char)0x80,0,(char)0x80,2,(char)0x80,4,(char)0x80,6,
        (char)0x80,8,(char)0x80,10,(char)0x80,12,(char)0x80,14);
    __m256i z=_mm256_xor_si256(x,make_key_vec(rk));
    z=_mm256_shuffle_epi8(tab,z);
    return _mm256_xor_si256(x,_mm256_shuffle_epi8(z,mv));
}
static __m256i perm_vec(__m256i x) {
    const __m256i m=_mm256_setr_epi8(
        1,2,11,6,3,0,9,4,7,10,13,14,5,8,15,12,
        1,2,11,6,3,0,9,4,7,10,13,14,5,8,15,12);
    return _mm256_shuffle_epi8(x,m);
}

void twine_encrypt8_avx2(const twine_ctx *ctx, const uint8_t in[64], uint8_t out[64]) {
    uint8_t n[128];
    for (unsigned b=0;b<8;++b) bytes_to_nibbles(in+8*b,8,n+16*b);
    __m256i x[4]; for(unsigned i=0;i<4;++i)x[i]=_mm256_loadu_si256((const __m256i*)(n+32*i));
    for(unsigned r=0;r<35;++r) for(unsigned i=0;i<4;++i)x[i]=perm_vec(f_vec(x[i],ctx->round_keys[r]));
    for(unsigned i=0;i<4;++i){x[i]=f_vec(x[i],ctx->round_keys[35]);_mm256_storeu_si256((__m256i*)(n+32*i),x[i]);}
    for(unsigned b=0;b<8;++b)nibbles_to_bytes(n+16*b,out+8*b);
}
