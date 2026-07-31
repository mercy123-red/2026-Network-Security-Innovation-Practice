CC ?= gcc
PYTHON ?= python3
ARCH := $(shell uname -m)

CPPFLAGS := -Iinclude -Isrc
CFLAGS ?= -O3 -std=c11 -Wall -Wextra -Wpedantic
LDFLAGS ?=

COMMON_SRC := src/sm3_scalar.c src/sm3_dispatch.c
ARCH_SRC :=
ARCH_CPPFLAGS :=

ifeq ($(ARCH),x86_64)
ARCH_SRC += src/x86/sm3_avx2.c src/x86/sm3_avx512.c
ARCH_CPPFLAGS += -DSM3_HAVE_AVX2=1 -DSM3_HAVE_AVX512=1
endif
ifeq ($(ARCH),amd64)
ARCH_SRC += src/x86/sm3_avx2.c src/x86/sm3_avx512.c
ARCH_CPPFLAGS += -DSM3_HAVE_AVX2=1 -DSM3_HAVE_AVX512=1
endif
ifeq ($(ARCH),aarch64)
ARCH_SRC += src/arm64/sm3_neon.c
ARCH_CPPFLAGS += -DSM3_HAVE_NEON=1
endif
ifeq ($(ARCH),arm64)
ARCH_SRC += src/arm64/sm3_neon.c
ARCH_CPPFLAGS += -DSM3_HAVE_NEON=1
endif

CPPFLAGS += $(ARCH_CPPFLAGS)
LIB_OBJ := $(COMMON_SRC:.c=.o) $(ARCH_SRC:.c=.o)
TEST_OBJ := tests/test_sm3.o
BENCH_OBJ := bench/sm3_benchmark.o

.PHONY: all test benchmark plot run_all sanitize arm64-syntax clean info

all: sm3_test sm3_benchmark

info:
	@echo "Detected architecture: $(ARCH)"
	@echo "Architecture sources: $(ARCH_SRC)"

sm3_test: $(LIB_OBJ) $(TEST_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

sm3_benchmark: $(LIB_OBJ) $(BENCH_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

src/x86/sm3_avx2.o: src/x86/sm3_avx2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -mavx2 -c $< -o $@

src/x86/sm3_avx512.o: src/x86/sm3_avx512.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -mavx512f -c $< -o $@

src/arm64/sm3_neon.o: src/arm64/sm3_neon.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -march=armv8-a+simd -c $< -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

test: sm3_test
	./sm3_test

benchmark: sm3_benchmark
	mkdir -p results
	./sm3_benchmark 8 results/sm3_benchmark.csv

plot: results/sm3_benchmark.csv
	MPLBACKEND=Agg $(PYTHON) scripts/plot_results.py results/sm3_benchmark.csv results/sm3_performance.png

run_all: clean all test benchmark plot

sanitize: clean
	$(MAKE) CFLAGS='-O1 -g -std=c11 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -fno-omit-frame-pointer' LDFLAGS='-fsanitize=address,undefined' all
	ASAN_OPTIONS=detect_leaks=1 ./sm3_test

# Syntax-check the ARM64 NEON implementation on x86 hosts with Clang.
arm64-syntax:
	clang --target=aarch64-none-elf -march=armv8-a+simd -ffreestanding \
		-Iinclude -Isrc -DSM3_HAVE_NEON=1 -Wall -Wextra -Wpedantic \
		-c src/arm64/sm3_neon.c -o /tmp/sm3_neon_arm64.o
	@echo "ARM64 NEON syntax check passed"

clean:
	rm -f $(COMMON_SRC:.c=.o) src/x86/*.o src/arm64/*.o tests/*.o bench/*.o
	rm -f sm3_test sm3_benchmark
