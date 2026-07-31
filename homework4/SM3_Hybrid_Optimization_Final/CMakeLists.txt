cmake_minimum_required(VERSION 3.16)
project(sm3_hybrid_optimization C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(sm3 STATIC
    src/sm3_scalar.c
    src/sm3_dispatch.c
)
target_include_directories(sm3 PUBLIC include PRIVATE src)
target_compile_options(sm3 PRIVATE -O3 -Wall -Wextra -Wpedantic)

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" SM3_PROCESSOR)
if(SM3_PROCESSOR MATCHES "x86_64|amd64")
    target_sources(sm3 PRIVATE src/x86/sm3_avx2.c src/x86/sm3_avx512.c)
    target_compile_definitions(sm3 PUBLIC SM3_HAVE_AVX2=1 SM3_HAVE_AVX512=1)
    set_source_files_properties(src/x86/sm3_avx2.c PROPERTIES COMPILE_OPTIONS "-mavx2")
    set_source_files_properties(src/x86/sm3_avx512.c PROPERTIES COMPILE_OPTIONS "-mavx512f")
elseif(SM3_PROCESSOR MATCHES "aarch64|arm64")
    target_sources(sm3 PRIVATE src/arm64/sm3_neon.c)
    target_compile_definitions(sm3 PUBLIC SM3_HAVE_NEON=1)
    set_source_files_properties(src/arm64/sm3_neon.c PROPERTIES COMPILE_OPTIONS "-march=armv8-a+simd")
endif()

add_executable(sm3_test tests/test_sm3.c)
target_link_libraries(sm3_test PRIVATE sm3)
target_compile_options(sm3_test PRIVATE -O3 -Wall -Wextra -Wpedantic)

add_executable(sm3_benchmark bench/sm3_benchmark.c)
target_link_libraries(sm3_benchmark PRIVATE sm3)
target_compile_options(sm3_benchmark PRIVATE -O3 -Wall -Wextra -Wpedantic)

enable_testing()
add_test(NAME sm3_correctness COMMAND sm3_test)
