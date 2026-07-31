#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sm4.h"
#include "sm4_ctr.h"

typedef void (*block_fn)(const sm4_ctx *, const uint8_t[16], uint8_t[16]);
typedef void (*ctr_fn)(const sm4_ctx *, const uint8_t[16], const uint8_t *, uint8_t *, size_t);

static double now_seconds(void) {
    struct timespec ts; if (clock_gettime(CLOCK_MONOTONIC,&ts)!=0) exit(EXIT_FAILURE);
    return (double)ts.tv_sec+(double)ts.tv_nsec*1e-9;
}
static int equal(const uint8_t *a,const uint8_t *b,size_t n){uint8_t d=0;for(size_t i=0;i<n;++i)d|=(uint8_t)(a[i]^b[i]);return d==0;}

static int check_block(const char *name, block_fn enc, block_fn dec,
                       const sm4_ctx *ctx, const uint8_t pt[16], const uint8_t ct[16]) {
    uint8_t x[16], y[16]; enc(ctx,pt,x); dec(ctx,x,y);
    const int ok=equal(x,ct,16)&&equal(y,pt,16);
    printf("[%-24s] %s\n",name,ok?"PASS":"FAIL"); return ok;
}

static double bench_block(const char *name, block_fn fn, const sm4_ctx *ctx,
                          size_t bytes, FILE *csv) {
    uint8_t in[16]={0},out[16]={0}; const size_t blocks=bytes/16U;
    const double start=now_seconds();
    for(size_t i=0;i<blocks;++i){in[0]=(uint8_t)i;in[7]^=out[3];fn(ctx,in,out);}
    const double speed=((double)bytes/(1024.0*1024.0))/(now_seconds()-start);
    printf("%-28s %10.2f MiB/s checksum=%02x\n",name,speed,out[0]);
    if (csv != NULL) {
        fprintf(csv, "%s,%.6f\n", name, speed);
    }
    return speed;
}

static double bench_avx2(const sm4_ctx *ctx,size_t bytes,FILE *csv){
    uint8_t in[128]={0},out[128]={0};const size_t groups=bytes/128U;
    const double start=now_seconds();for(size_t i=0;i<groups;++i){in[0]=(uint8_t)i;in[73]^=out[5];sm4_encrypt8_avx2(ctx,in,out);}
    const double speed=((double)(groups*128U)/(1024.0*1024.0))/(now_seconds()-start);
    printf("%-28s %10.2f MiB/s checksum=%02x\n","SM4 AVX2 x8",speed,out[0]);if(csv)fprintf(csv,"SM4 AVX2 x8,%.6f\n",speed);return speed;
}

static double bench_ctr(const char *name,ctr_fn fn,const sm4_ctx *ctx,const uint8_t ctr[16],uint8_t *in,uint8_t*out,size_t bytes,FILE*csv){
    const double start=now_seconds();fn(ctx,ctr,in,out,bytes);const double speed=((double)bytes/(1024.0*1024.0))/(now_seconds()-start);
    printf("%-28s %10.2f MiB/s checksum=%02x\n",name,speed,out[bytes-1]);if(csv)fprintf(csv,"%s,%.6f\n",name,speed);return speed;
}

int main(int argc,char**argv){
    size_t mib=64;if(argc==2){char*e=NULL;errno=0;unsigned long v=strtoul(argv[1],&e,10);if(errno||e==argv[1]||*e||v==0)return EXIT_FAILURE;mib=(size_t)v;}
    const uint8_t key[16]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
    const uint8_t pt[16]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
    const uint8_t ct[16]={0x68,0x1e,0xdf,0x34,0xd2,0x06,0x96,0x5e,0x86,0xb3,0xe9,0x4f,0x53,0x6e,0x42,0x46};
    sm4_ctx ctx;if(sm4_init(&ctx,key)!=0)return EXIT_FAILURE;
    puts("SM4 known-answer tests (GB/T 32907 example)");int ok=1;
    ok&=check_block("SM4 basic",sm4_encrypt_basic,sm4_decrypt_basic,&ctx,pt,ct);
    ok&=check_block("SM4 T-table",sm4_encrypt_ttable,sm4_decrypt_ttable,&ctx,pt,ct);
    uint8_t in8[128],out8[128],back8[128];for(unsigned i=0;i<8;++i)memcpy(in8+16U*i,pt,16);
    sm4_encrypt8_avx2(&ctx,in8,out8);sm4_decrypt8_avx2(&ctx,out8,back8);
    for(unsigned i=0;i<8;++i)ok&=equal(out8+16U*i,ct,16)&&equal(back8+16U*i,pt,16);
    printf("[%-24s] %s\n","SM4 AVX2 x8",ok?"PASS":"FAIL");
    uint8_t ctr[16]={0},plain[257],a[257],b[257],recover[257];for(size_t i=0;i<sizeof(plain);++i)plain[i]=(uint8_t)(i*23U+9U);
    sm4_ctr_crypt_basic(&ctx,ctr,plain,a,sizeof(a));sm4_ctr_crypt_avx2(&ctx,ctr,plain,b,sizeof(b));sm4_ctr_crypt_avx2(&ctx,ctr,b,recover,sizeof(recover));
    const int ctr_ok=equal(a,b,sizeof(a))&&equal(recover,plain,sizeof(plain));printf("[%-24s] %s\n","SM4 CTR AVX2+tail",ctr_ok?"PASS":"FAIL");ok&=ctr_ok;
    if(!ok)return EXIT_FAILURE;
    const size_t bytes=mib*1024U*1024U;uint8_t*buf=aligned_alloc(32,(bytes+31U)&~(size_t)31U);uint8_t*out=aligned_alloc(32,(bytes+31U)&~(size_t)31U);
    if(!buf||!out){free(buf);free(out);return EXIT_FAILURE;}for(size_t i=0;i<bytes;++i)buf[i]=(uint8_t)(i*31U+7U);
    if(system("mkdir -p results")!=0){fputs("warning: could not create results directory\n",stderr);}
    FILE*csv=fopen("results/sm4_benchmark.csv","w");if(csv)fputs("implementation,mib_per_second\n",csv);
    printf("\nSM4 benchmark size: %zu MiB\n",mib);bench_block("SM4 basic",sm4_encrypt_basic,&ctx,bytes,csv);bench_block("SM4 T-table",sm4_encrypt_ttable,&ctx,bytes,csv);bench_avx2(&ctx,bytes,csv);
    bench_ctr("SM4-CTR basic",sm4_ctr_crypt_basic,&ctx,ctr,buf,out,bytes,csv);bench_ctr("SM4-CTR T-table",sm4_ctr_crypt_ttable,&ctx,ctr,buf,out,bytes,csv);bench_ctr("SM4-CTR AVX2 x8",sm4_ctr_crypt_avx2,&ctx,ctr,buf,out,bytes,csv);
    if (csv != NULL) {
        fclose(csv);
    }
    free(buf);
    free(out);
    return EXIT_SUCCESS;
}
