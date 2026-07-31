#!/usr/bin/env python3
from __future__ import annotations
import csv
from pathlib import Path
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

root = Path(__file__).resolve().parents[1]
path = root / "results" / "all_benchmarks.csv"
if not path.exists():
    raise SystemExit("run 'make benchmark' or scripts/merge_results.py first")

labels: list[str] = []
values: list[float] = []
with path.open(newline="", encoding="utf-8") as handle:
    for row in csv.DictReader(handle):
        labels.append(row["implementation"])
        values.append(float(row["mib_per_second"]))

fig, ax = plt.subplots(figsize=(12, max(6, 0.38 * len(labels))))
y = list(range(len(labels)))
ax.barh(y, values)
ax.set_yticks(y, labels)
ax.invert_yaxis()
ax.set_xlabel("Throughput (MiB/s)")
ax.set_title("Symmetric Cipher Software Optimization Benchmark")
ax.grid(axis="x", alpha=0.25)
fig.tight_layout()
out = root / "results" / "performance.png"
fig.savefig(out, dpi=180)
print(f"wrote {out}")
