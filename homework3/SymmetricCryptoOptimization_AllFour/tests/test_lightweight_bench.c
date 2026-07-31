#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gift64.h"
#include "twine.h"

static double now_s(void){struct timespec t;if(clock_gettime(CLOCK_MONOTONIC,&t)){perror("clock_gettime");exit(1);}return t.tv_sec+t.tv_nsec*1e-9;}
static int eq(const uint8_t*a,const uint8_t*b,size_t n){unsigned d=0;for(size_t i=0;i<n;++i)d|=a[i]^b[i];return d==0;}
static void status(const char*n,int ok){printf("[%-28s] %s\n",n,ok?"PASS":"FAIL");}

typedef void (*gift_fn)(const gift64_ctx*,const uint8_t*,uint8_t*);
typedef void (*twine_fn)(const twine_ctx*,const uint8_t*,uint8_t*);
static double bench_gift(const char*n,gift_fn f,const gift64_ctx*c,size_t bytes,FILE*csv){uint8_t in[8]={0},out[8]={0};size_t blocks=bytes/8;double s=now_s();for(size_t i=0;i<blocks;++i){in[0]=(uint8_t)i;in[7]^=out[2];f(c,in,out);}double mb=(bytes/1048576.0)/(now_s()-s);printf("%-30s %10.2f MiB/s checksum=%02x\n",n,mb,out[0]);if(csv)fprintf(csv,"%s,%.6f\n",n,mb);return mb;}
static double bench_gift8(const gift64_ctx*c,size_t bytes,FILE*csv){uint8_t in[64]={0},out[64]={0};size_t groups=bytes/64;double s=now_s();for(size_t i=0;i<groups;++i){in[0]=(uint8_t)i;in[63]^=out[5];gift64_encrypt8_avx2(c,in,out);}double mb=((groups*64)/1048576.0)/(now_s()-s);printf("%-30s %10.2f MiB/s checksum=%02x\n","GIFT-64 AVX2 x8",mb,out[0]);if(csv)fprintf(csv,"GIFT-64 AVX2 x8,%.6f\n",mb);return mb;}
static double bench_twine(const char*n,twine_fn f,const twine_ctx*c,size_t bytes,FILE*csv){uint8_t in[8]={0},out[8]={0};size_t blocks=bytes/8;double s=now_s();for(size_t i=0;i<blocks;++i){in[0]=(uint8_t)i;in[7]^=out[2];f(c,in,out);}double mb=(bytes/1048576.0)/(now_s()-s);printf("%-30s %10.2f MiB/s checksum=%02x\n",n,mb,out[0]);if(csv)fprintf(csv,"%s,%.6f\n",n,mb);return mb;}
static double bench_twine8(const char*n,const twine_ctx*c,size_t bytes,FILE*csv){uint8_t in[64]={0},out[64]={0};size_t groups=bytes/64;double s=now_s();for(size_t i=0;i<groups;++i){in[0]=(uint8_t)i;in[63]^=out[5];twine_encrypt8_avx2(c,in,out);}double mb=((groups*64)/1048576.0)/(now_s()-s);printf("%-30s %10.2f MiB/s checksum=%02x\n",n,mb,out[0]);if(csv)fprintf(csv,"%s,%.6f\n",n,mb);return mb;}

int main(int argc,char**argv){
 size_t mib=16;if(argc==2){char*e;errno=0;unsigned long v=strtoul(argv[1],&e,10);if(errno||*e||!v){fprintf(stderr,"usage: %s [MiB]\n",argv[0]);return 1;}mib=v;}
 int ok=1;uint8_t out[64],back[8];
 const uint8_t gkey[16]={0},gpt[8]={0},gct[8]={0xf6,0x2b,0xc3,0xef,0x34,0xf7,0x75,0xac};gift64_ctx gc;gift64_init(&gc,gkey);
 gift64_encrypt_basic(&gc,gpt,out);status("GIFT-64 official vector 1",eq(out,gct,8));ok&=eq(out,gct,8);
 gift64_encrypt_ttable(&gc,gpt,out);status("GIFT-64 T-table vector 1",eq(out,gct,8));ok&=eq(out,gct,8);
 gift64_decrypt_basic(&gc,gct,back);status("GIFT-64 decrypt vector 1",eq(back,gpt,8));ok&=eq(back,gpt,8);
 uint8_t gin[64];for(unsigned i=0;i<8;++i)memcpy(gin+8*i,gpt,8);gift64_encrypt8_avx2(&gc,gin,out);int gok=1;for(unsigned i=0;i<8;++i)gok&=eq(out+8*i,gct,8);status("GIFT-64 AVX2 x8 vector 1",gok);ok&=gok;

 const uint8_t gpt2[8]={0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
 const uint8_t gkey2[16]={0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
 const uint8_t gct2[8]={0xc1,0xb7,0x1f,0x66,0x16,0x0f,0xf5,0x87};
 gift64_ctx gc2;gift64_init(&gc2,gkey2);gift64_encrypt_basic(&gc2,gpt2,out);status("GIFT-64 official vector 2",eq(out,gct2,8));ok&=eq(out,gct2,8);gift64_encrypt_ttable(&gc2,gpt2,out);status("GIFT-64 T-table vector 2",eq(out,gct2,8));ok&=eq(out,gct2,8);gift64_decrypt_basic(&gc2,gct2,back);status("GIFT-64 decrypt vector 2",eq(back,gpt2,8));ok&=eq(back,gpt2,8);

 const uint8_t gpt3[8]={0xc4,0x50,0xc7,0x72,0x7a,0x9b,0x8a,0x7d};
 const uint8_t gkey3[16]={0xbd,0x91,0x73,0x1e,0xb6,0xbc,0x27,0x13,0xa1,0xf9,0xf6,0xff,0xc7,0x50,0x44,0xe7};
 const uint8_t gct3[8]={0xe3,0x27,0x28,0x85,0xfa,0x94,0xba,0x8b};
 gift64_ctx gc3;gift64_init(&gc3,gkey3);gift64_encrypt_basic(&gc3,gpt3,out);status("GIFT-64 official vector 3",eq(out,gct3,8));ok&=eq(out,gct3,8);gift64_encrypt_ttable(&gc3,gpt3,out);status("GIFT-64 T-table vector 3",eq(out,gct3,8));ok&=eq(out,gct3,8);gift64_decrypt_basic(&gc3,gct3,back);status("GIFT-64 decrypt vector 3",eq(back,gpt3,8));ok&=eq(back,gpt3,8);
 const uint8_t pt[8]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
 const uint8_t k80[10]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
 const uint8_t c80[8]={0x7c,0x1f,0x0f,0x80,0xb1,0xdf,0x9c,0x28};
 const uint8_t k128[16]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
 const uint8_t c128[8]={0x97,0x9f,0xf9,0xb3,0x79,0xb5,0xa9,0xb8};
 twine_ctx t80,t128;twine80_init(&t80,k80);twine128_init(&t128,k128);
 twine_encrypt_basic(&t80,pt,out);status("TWINE-80 official vector",eq(out,c80,8));ok&=eq(out,c80,8);twine_decrypt_basic(&t80,c80,back);status("TWINE-80 decrypt",eq(back,pt,8));ok&=eq(back,pt,8);
 twine_encrypt_basic(&t128,pt,out);status("TWINE-128 official vector",eq(out,c128,8));ok&=eq(out,c128,8);twine_decrypt_basic(&t128,c128,back);status("TWINE-128 decrypt",eq(back,pt,8));ok&=eq(back,pt,8);
 uint8_t tin[64];for(unsigned i=0;i<8;++i)memcpy(tin+8*i,pt,8);twine_encrypt8_avx2(&t80,tin,out);int tok=1;for(unsigned i=0;i<8;++i)tok&=eq(out+8*i,c80,8);status("TWINE-80 AVX2 x8",tok);ok&=tok;twine_encrypt8_avx2(&t128,tin,out);tok=1;for(unsigned i=0;i<8;++i)tok&=eq(out+8*i,c128,8);status("TWINE-128 AVX2 x8",tok);ok&=tok;
 if(!ok)return 1;
 (void)!system("mkdir -p results");FILE*csv=fopen("results/lightweight_benchmark.csv","w");if(csv)fputs("implementation,mib_per_second\n",csv);size_t bytes=mib*1048576U;
 printf("\nLightweight benchmark size: %zu MiB\n",mib);bench_gift("GIFT-64 basic",gift64_encrypt_basic,&gc,bytes,csv);bench_gift("GIFT-64 T-table",gift64_encrypt_ttable,&gc,bytes,csv);bench_gift8(&gc,bytes,csv);bench_twine("TWINE-80 basic",twine_encrypt_basic,&t80,bytes,csv);bench_twine8("TWINE-80 AVX2 x8",&t80,bytes,csv);bench_twine("TWINE-128 basic",twine_encrypt_basic,&t128,bytes,csv);bench_twine8("TWINE-128 AVX2 x8",&t128,bytes,csv);if(csv)fclose(csv);puts("CSV written to results/lightweight_benchmark.csv");return 0;
}
