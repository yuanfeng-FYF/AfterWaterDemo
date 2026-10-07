$ErrorActionPreference = 'Stop'
$manifest = Get-Content -LiteralPath (Join-Path $PSScriptRoot 'BACKUP-MANIFEST.json') -Raw -Encoding UTF8 | ConvertFrom-Json
$failures = @()
foreach ($entry in $manifest.files) {
    $path = Join-Path $PSScriptRoot $entry.path
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { $failures += "Missing: $($entry.path)"; continue }
    if ((Get-Item -LiteralPath $path).Length -ne $entry.bytes) { $failures += "Size mismatch: $($entry.path)"; continue }
    if ((Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash -ne $entry.sha256) { $failures += "Hash mismatch: $($entry.path)" }
}
if ($failures.Count) { $failures | Write-Output; throw "$($failures.Count) file(s) differ from the initial backup. Run git lfs pull if assets are missing." }
Write-Output "PASS: all $($manifest.files.Count) initial backup files match SHA-256."
