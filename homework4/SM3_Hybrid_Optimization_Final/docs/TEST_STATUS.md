# Test status before packaging

Verified on the build host:

- Release build with GCC and `-Wall -Wextra -Wpedantic`: passed without warnings.
- SM3 official known-answer vectors: passed.
- Streaming API: passed.
- AVX2 multi-buffer implementation: passed scalar cross-checks for boundary lengths.
- AVX-512F multi-buffer implementation: passed scalar cross-checks for boundary lengths on the build host.
- AddressSanitizer and UndefinedBehaviorSanitizer: passed.
- ARM64 NEON source: successfully cross-compiled with Clang target `aarch64-none-elf` and `-march=armv8-a+simd`.
- Benchmark CSV and headless Matplotlib PNG generation: passed.

The current build host is x86-64, so ARM64 NEON execution speed must be measured on an ARM64 machine. Runtime correctness on ARM64 is additionally checked by the same `sm3_test` binary when built and run on that target.
