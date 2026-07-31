CC ?= gcc
CPPFLAGS := -Iinclude
CFLAGS ?= -O3 -std=gnu11 -Wall -Wextra -Wpedantic
ISAFLAGS := -mssse3 -maes -mavx2 -mvaes -mpclmul
LDFLAGS ?=

LIB_SOURCES := \
	src/aes_common.c \
	src/aes_basic.c \
	src/aes_ttable.c \
	src/aes_shuffle.c \
	src/aes_aesni.c \
	src/aes_vaes.c \
	src/aes_ctr.c \
	src/aes_gcm.c \
	src/aes_xts.c \
	src/sm4_common.c \
	src/sm4_basic.c \
	src/sm4_ttable.c \
	src/sm4_avx2.c \
	src/sm4_ctr.c \
	src/gift64.c \
	src/twine.c

LIB_OBJECTS := $(LIB_SOURCES:.c=.o)
AES_TEST_OBJECT := tests/test_bench.o
CTR_TEST_OBJECT := tests/test_ctr_bench.o
GCM_TEST_OBJECT := tests/test_gcm_bench.o
XTS_TEST_OBJECT := tests/test_xts_bench.o
SM4_TEST_OBJECT := tests/test_sm4_bench.o
LIGHTWEIGHT_TEST_OBJECT := tests/test_lightweight_bench.o

TARGETS := aes_benchmark ctr_benchmark gcm_benchmark xts_benchmark sm4_benchmark lightweight_benchmark

.PHONY: all test test-aes test-ctr test-gcm test-xts test-sm4 test-lightweight \
        benchmark plot sanitize clean

all: $(TARGETS)

aes_benchmark: $(LIB_OBJECTS) $(AES_TEST_OBJECT)
	$(CC) $^ $(LDFLAGS) -o $@

ctr_benchmark: $(LIB_OBJECTS) $(CTR_TEST_OBJECT)
	$(CC) $^ $(LDFLAGS) -o $@

gcm_benchmark: $(LIB_OBJECTS) $(GCM_TEST_OBJECT)
	$(CC) $^ $(LDFLAGS) -o $@

xts_benchmark: $(LIB_OBJECTS) $(XTS_TEST_OBJECT)
	$(CC) $^ $(LDFLAGS) -o $@

sm4_benchmark: $(LIB_OBJECTS) $(SM4_TEST_OBJECT)
	$(CC) $^ $(LDFLAGS) -o $@

lightweight_benchmark: $(LIB_OBJECTS) $(LIGHTWEIGHT_TEST_OBJECT)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(ISAFLAGS) -c $< -o $@

test: test-aes test-ctr test-gcm test-xts test-sm4 test-lightweight

test-aes: aes_benchmark
	./aes_benchmark 2

test-ctr: ctr_benchmark
	./ctr_benchmark 2

test-gcm: gcm_benchmark
	./gcm_benchmark 2

test-xts: xts_benchmark
	./xts_benchmark 2

test-sm4: sm4_benchmark
	./sm4_benchmark 2

test-lightweight: lightweight_benchmark
	./lightweight_benchmark 2

benchmark: all
	./aes_benchmark 64
	./ctr_benchmark 128
	./gcm_benchmark 64
	./xts_benchmark 128
	./sm4_benchmark 64
	./lightweight_benchmark 8
	python3 scripts/merge_results.py

plot:
	python3 scripts/merge_results.py
	MPLBACKEND=Agg python3 scripts/plot_results.py

sanitize:
	$(MAKE) clean
	$(MAKE) CFLAGS='-O1 -g -std=gnu11 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -fno-omit-frame-pointer' LDFLAGS='-fsanitize=address,undefined' all
	ASAN_OPTIONS=detect_leaks=1 ./aes_benchmark 1
	ASAN_OPTIONS=detect_leaks=1 ./ctr_benchmark 1
	ASAN_OPTIONS=detect_leaks=1 ./gcm_benchmark 1
	ASAN_OPTIONS=detect_leaks=1 ./xts_benchmark 1
	ASAN_OPTIONS=detect_leaks=1 ./sm4_benchmark 1
	ASAN_OPTIONS=detect_leaks=1 ./lightweight_benchmark 1

clean:
	rm -f $(LIB_OBJECTS) $(AES_TEST_OBJECT) $(CTR_TEST_OBJECT) $(GCM_TEST_OBJECT) $(XTS_TEST_OBJECT) $(SM4_TEST_OBJECT) $(LIGHTWEIGHT_TEST_OBJECT)
	rm -f $(TARGETS)
	rm -f results/*_benchmark.csv results/all_benchmarks.csv results/performance.png
