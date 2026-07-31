#!/usr/bin/env python3
from __future__ import annotations
import csv
from pathlib import Path

root = Path(__file__).resolve().parents[1]
results = root / "results"
files = [
    results / "aes_benchmark.csv",
    results / "ctr_benchmark.csv",
    results / "gcm_benchmark.csv",
    results / "xts_benchmark.csv",
    results / "sm4_benchmark.csv",
    results / "lightweight_benchmark.csv",
]
rows: list[dict[str, str]] = []
for path in files:
    if not path.exists():
        continue
    group = path.stem.replace("_benchmark", "").upper()
    with path.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            rows.append({
                "group": group,
                "implementation": row["implementation"],
                "mib_per_second": row["mib_per_second"],
            })

out = results / "all_benchmarks.csv"
with out.open("w", newline="", encoding="utf-8") as handle:
    writer = csv.DictWriter(handle, fieldnames=["group", "implementation", "mib_per_second"])
    writer.writeheader()
    writer.writerows(rows)
print(f"wrote {out} ({len(rows)} rows)")
