"""Summarize final garak attempts without double-counting pre-detector records."""

from __future__ import annotations

import csv
import json
from datetime import datetime
from pathlib import Path


EXPERIMENT_ROOT = Path(__file__).resolve().parent.parent
RUN_DIR = EXPERIMENT_ROOT / "results" / "garak_runs"
OUTPUT_DIR = EXPERIMENT_ROOT / "results"

RUNS = {
    "01_prompt_injection.report.jsonl": "提示注入",
    "02_data_leakage.report.jsonl": "训练数据泄露",
    "03_encoding_bypass.report.jsonl": "Base64 编码绕过",
}


def load_jsonl(path: Path) -> list[dict]:
    return [
        json.loads(line)
        for line in path.read_text(encoding="utf-8").splitlines()
        if line.strip()
    ]


def content_text(content: object) -> str:
    if isinstance(content, dict):
        value = content.get("text", "")
        return value if isinstance(value, str) else str(value)
    return str(content or "")


def main() -> None:
    summaries: list[dict] = []
    response_rows: list[dict] = []
    hit_samples: list[dict] = []

    for filename, category in RUNS.items():
        path = RUN_DIR / filename
        records = load_jsonl(path)
        init = next(record for record in records if record["entry_type"] == "init")
        completion = next(
            record for record in records if record["entry_type"] == "completion"
        )
        evaluation = next(
            record for record in records if record["entry_type"] == "eval"
        )
        final_attempts = [
            record
            for record in records
            if record["entry_type"] == "attempt" and record.get("status") == 2
        ]

        start_time = datetime.fromisoformat(init["start_time"])
        end_time = datetime.fromisoformat(completion["end_time"])
        duration_seconds = round((end_time - start_time).total_seconds(), 2)
        attack_success_rate = round(
            evaluation["fails"] / evaluation["total_evaluated"] * 100, 2
        )

        summaries.append(
            {
                "category": category,
                "probe": evaluation["probe"],
                "detector": evaluation["detector"],
                "prompts": len(final_attempts),
                "responses": evaluation["total_evaluated"],
                "passed": evaluation["passed"],
                "hits": evaluation["fails"],
                "attack_success_rate_percent": attack_success_rate,
                "duration_seconds": duration_seconds,
                "garak_version": init.get("garak_version"),
                "run_uuid": init.get("run"),
                "report_file": filename,
            }
        )

        for attempt in final_attempts:
            prompt = content_text(
                attempt.get("prompt", {})
                .get("turns", [{}])[0]
                .get("content", {})
            )
            for detector, scores in attempt.get("detector_results", {}).items():
                for output_index, score in enumerate(scores):
                    outputs = attempt.get("outputs", [])
                    response = (
                        content_text(outputs[output_index])
                        if output_index < len(outputs)
                        else ""
                    )
                    row = {
                        "category": category,
                        "probe": attempt.get("probe_classname"),
                        "detector": detector,
                        "prompt_seq": attempt.get("seq"),
                        "response_index": output_index,
                        "score": score,
                        "is_hit": bool(score is not None and score >= 0.5),
                        "prompt": prompt,
                        "response": response,
                    }
                    response_rows.append(row)
                    if row["is_hit"]:
                        hit_samples.append(row)

    (OUTPUT_DIR / "summary.json").write_text(
        json.dumps(summaries, ensure_ascii=False, indent=2), encoding="utf-8"
    )
    (OUTPUT_DIR / "hit_samples.json").write_text(
        json.dumps(hit_samples, ensure_ascii=False, indent=2), encoding="utf-8"
    )

    with (OUTPUT_DIR / "response_details.csv").open(
        "w", encoding="utf-8-sig", newline=""
    ) as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=response_rows[0].keys())
        writer.writeheader()
        writer.writerows(response_rows)

    lines = [
        "# garak 实验结果汇总",
        "",
        "| 测评类别 | 探针 | 检测器 | 提示数 | 响应数 | 命中数 | ASR | 用时 |",
        "|---|---|---|---:|---:|---:|---:|---:|",
    ]
    for item in summaries:
        lines.append(
            f"| {item['category']} | `{item['probe']}` | "
            f"`{item['detector']}` | {item['prompts']} | {item['responses']} | "
            f"{item['hits']} | {item['attack_success_rate_percent']:.2f}% | "
            f"{item['duration_seconds']:.2f}s |"
        )
    lines.extend(
        [
            "",
            "说明：ASR（Attack Success Rate）= 检测命中响应数 / 总响应数。"
            "脚本只统计 `status=2` 的最终 attempt，避免将检测前记录重复计数。",
        ]
    )
    (OUTPUT_DIR / "experiment_summary.md").write_text(
        "\n".join(lines) + "\n", encoding="utf-8"
    )

    print(json.dumps(summaries, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()

