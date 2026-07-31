#!/usr/bin/env bash
set -euo pipefail
make clean
make -j"$(nproc)"
make test
make benchmark
if python3 -c 'import matplotlib' >/dev/null 2>&1; then
  MPLBACKEND=Agg make plot
else
  echo "matplotlib not installed; CSV files were generated, chart skipped."
fi
