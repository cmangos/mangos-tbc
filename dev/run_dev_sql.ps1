# =============================================
# run_dev_sql.ps1 - apply all .sql files in this folder in filename order
#
# Usage:
#   double-click run_dev_sql.bat, or:
#   powershell -NoProfile -ExecutionPolicy Bypass -File .\run_dev_sql.ps1
#
# Optional parameters:
#   -Database <name>   -Host <host>   -Port <port>
#   -User <user>       -Pass <pass>   -DevDir <sql folder>
#   -StopOnError   (stop on first failure; default: continue with next file)
#   -WhatIf        (preflight only, run nothing)
#
# Connection info is read from mangosd.conf (WorldDatabaseInfo) when found;
# falls back to 127.0.0.1:3306 root/qwerty tbcmangos.
# =============================================

param(
    [string]$DevDir = "",
    [string]$HostName = "",
    [int]$Port = 0,
    [string]$User = "",
    [string]$Pass = "",
    [string]$Database = "",
    [switch]$StopOnError,
    [switch]$WhatIf
)

$ErrorActionPreference = 'Stop'

# ---------- 1. folder + connection info ----------
if (-not $DevDir) { $DevDir = $PSScriptRoot }
if (-not (Test-Path -LiteralPath $DevDir)) { throw "Directory not found: $DevDir" }

$confCandidates = @(
    (Join-Path $DevDir '..\..\x64_Debug\mangosd.conf'),
    (Join-Path $DevDir '..\..\build1\bin\x64_Debug\mangosd.conf')
)
$conf = $confCandidates | Where-Object { Test-Path -LiteralPath $_ } | Select-Object -First 1

if ($conf) {
    $line = Select-String -LiteralPath $conf -Pattern '^\s*WorldDatabaseInfo\s*=' | Select-Object -First 1
    if ($line) {
        $m = [regex]::Match($line.Line, '"([^"]+)"')
        if ($m.Success) {
            $parts = $m.Groups[1].Value -split ';'
            if ($parts.Count -ge 5) {
                if (-not $HostName) { $HostName = $parts[0] }
                if (-not $Port)     { $Port = [int]$parts[1] }
                if (-not $User)     { $User = $parts[2] }
                if (-not $Pass)     { $Pass = $parts[3] }
                if (-not $Database) { $Database = $parts[4] }
            }
        }
    }
}
if (-not $HostName) { $HostName = '127.0.0.1' }
if (-not $Port)     { $Port = 3306 }
if (-not $User)     { $User = 'root' }
if (-not $Pass)     { $Pass = 'qwerty' }
if (-not $Database) { $Database = 'tbcmangos' }

# ---------- 2. locate mysql client ----------
$mysql = (Get-Command mysql.exe -ErrorAction SilentlyContinue).Source
if (-not $mysql) {
    $candidates = @(
        'C:\Program Files\MySQL\MySQL Server 9.3\bin\mysql.exe',
        'C:\Program Files\MySQL\MySQL Server 8.4\bin\mysql.exe',
        'C:\Program Files\MySQL\MySQL Server 8.0\bin\mysql.exe'
    )
    $candidates += Get-ChildItem 'C:\Program Files\MySQL' -Filter mysql.exe -Recurse -ErrorAction SilentlyContinue | Select-Object -ExpandProperty FullName
    $mysql = $candidates | Where-Object { Test-Path -LiteralPath $_ } | Select-Object -First 1
}
if (-not $mysql) { throw 'mysql.exe not found; install MySQL client or add mysql to PATH' }

$files = Get-ChildItem -LiteralPath $DevDir -Filter '*.sql' | Sort-Object Name
if ($files.Count -eq 0) { Write-Host 'No .sql files in dev directory'; return }

Write-Host "Database : $Database@$HostName`:$Port"
Write-Host "User     : $User"
Write-Host "Client   : $mysql"
Write-Host "Folder   : $DevDir"
Write-Host "Files    : $($files.Count) (in filename order)"
$files | ForEach-Object { Write-Host ("  - " + $_.Name) }

if ($WhatIf) { Write-Host '(WhatIf: preflight only, nothing was executed)'; return }

# ---------- 3. execute each file (raw bytes to mysql, no encoding conversion) ----------
$env:MYSQL_PWD = $Pass
$ok = 0
$failed = @()

foreach ($f in $files) {
    $psi = New-Object System.Diagnostics.ProcessStartInfo
    $psi.FileName = $mysql
    $psi.Arguments = "--host=$HostName --port=$Port --user=$User --default-character-set=utf8 --database=$Database --batch"
    $psi.UseShellExecute = $false
    $psi.RedirectStandardInput = $true
    $psi.RedirectStandardOutput = $true
    $psi.RedirectStandardError = $true

    Write-Host ("[" + (Get-Date -Format 'HH:mm:ss') + "] Executing: " + $f.Name)
    try {
        $p = [System.Diagnostics.Process]::Start($psi)
        $outTask = $p.StandardOutput.ReadToEndAsync()
        $errTask = $p.StandardError.ReadToEndAsync()
        $bytes = [System.IO.File]::ReadAllBytes($f.FullName)
        $p.StandardInput.BaseStream.Write($bytes, 0, $bytes.Length)
        $p.StandardInput.Close()
        $p.WaitForExit()
        $stdout = $outTask.Result
        $stderr = $errTask.Result

        if ($p.ExitCode -eq 0) {
            $ok++
            Write-Host "  OK"
        } else {
            Write-Host ("  FAILED, exit code " + $p.ExitCode)
            if ($stderr) { Write-Host $stderr }
            if ($stdout) { Write-Host $stdout }
            $failed += $f.Name
            if ($StopOnError) { break }
        }
    }
    catch {
        Write-Host ("  Exception: " + $_.Exception.Message)
        $failed += $f.Name
        if ($StopOnError) { break }
    }
}

Remove-Item Env:MYSQL_PWD -ErrorAction SilentlyContinue

Write-Host ""
Write-Host ("Done: succeeded " + $ok + " / " + $files.Count)
if ($failed.Count -gt 0) { Write-Host ("Failed files: " + ($failed -join ', ')) }
