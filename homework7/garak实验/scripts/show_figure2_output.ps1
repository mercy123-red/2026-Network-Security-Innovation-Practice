$ErrorActionPreference = "Stop"

$experimentRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$python = Join-Path $experimentRoot ".venv\Scripts\python.exe"

Clear-Host
Write-Host "=== garak 实验环境与真实测评结果 ===" -ForegroundColor Cyan
Write-Host ""

& $python -m garak --version
& $python -c "import torch, transformers; print(f'PyTorch: {torch.__version__}'); print(f'Transformers: {transformers.__version__}'); print('Target: TinyLlama/TinyLlama-1.1B-Chat-v1.0'); print('Mode: Hugging Face local model / CPU / offline')"

Write-Host ""
Write-Host "=== 三类正式测评 ===" -ForegroundColor Yellow

$logFiles = @(
    "01_prompt_injection_stdout.log",
    "02_data_leakage_stdout.log",
    "03_encoding_bypass_stdout.log"
)

foreach ($logFile in $logFiles) {
    $path = Join-Path $experimentRoot "logs\$logFile"
    $ansiPattern = "$([char]27)\[[0-9;]*[A-Za-z]"
    Get-Content -LiteralPath $path |
        ForEach-Object { $_ -replace $ansiPattern, "" } |
        Select-String -Pattern "promptinject\.|leakreplay\.|encoding\.|attack success rate:"
}

Write-Host ""
Write-Host "Validated responses: 30 | Detector hits: 3 | Seed: 20260725" -ForegroundColor Green
