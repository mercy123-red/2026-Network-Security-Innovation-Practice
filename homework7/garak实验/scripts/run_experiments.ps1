$ErrorActionPreference = "Stop"

$experimentRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$python = Join-Path $experimentRoot ".venv\Scripts\python.exe"

if (-not (Test-Path -LiteralPath $python)) {
    throw "未找到隔离环境：$python"
}

$env:HF_HUB_OFFLINE = "1"
$env:TRANSFORMERS_OFFLINE = "1"
$env:TOKENIZERS_PARALLELISM = "false"
$model = "TinyLlama/TinyLlama-1.1B-Chat-v1.0"

$runs = @(
    @{
        Name = "01_prompt_injection"
        Config = "experiment.yaml"
        Probe = "promptinject.HijackKillHumans"
    },
    @{
        Name = "02_data_leakage"
        Config = "data_leakage.yaml"
        Probe = "leakreplay.PotterCloze"
    },
    @{
        Name = "03_encoding_bypass"
        Config = "experiment.yaml"
        Probe = "encoding.InjectBase64"
    }
)

foreach ($run in $runs) {
    $config = Join-Path $experimentRoot ("configs\" + $run.Config)
    $stdout = Join-Path $experimentRoot ("logs\" + $run.Name + "_stdout.log")
    $stderr = Join-Path $experimentRoot ("logs\" + $run.Name + "_stderr.log")

    & $python -m garak `
        --config $config `
        --target_type huggingface.Model `
        --target_name $model `
        --probes $run.Probe `
        --report_prefix $run.Name `
        1> $stdout 2> $stderr

    if ($LASTEXITCODE -ne 0) {
        throw "$($run.Name) 运行失败，检查 $stderr"
    }
}

& $python (Join-Path $PSScriptRoot "summarize_results.py")

