#!/usr/bin/env python3
import csv
import sys
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def main() -> int:
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} input.csv output.png", file=sys.stderr)
        return 2

    input_path = Path(sys.argv[1])
    output_path = Path(sys.argv[2])
    names, speeds = [], []
    with input_path.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            names.append(row["implementation"])
            speeds.append(float(row["mib_per_second"]))

    fig, ax = plt.subplots(figsize=(10, 5.5))
    bars = ax.bar(names, speeds)
    ax.set_ylabel("Throughput (MiB/s)")
    ax.set_title("SM3 scalar and SIMD/GPR hybrid implementations")
    ax.tick_params(axis="x", rotation=20)
    ax.grid(axis="y", linestyle="--", alpha=0.35)
    for bar, value in zip(bars, speeds):
        ax.text(bar.get_x() + bar.get_width()/2, value, f"{value:.1f}",
                ha="center", va="bottom", fontsize=9)
    fig.tight_layout()
    output_path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(output_path, dpi=180)
    print(f"wrote {output_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
