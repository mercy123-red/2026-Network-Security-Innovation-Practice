#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"
make clean
make -j"$(nproc)"
make test
make benchmark
make plot

echo
echo "All tests and benchmarks completed."
echo "CSV: results/sm3_benchmark.csv"
echo "Plot: results/sm3_performance.png"
