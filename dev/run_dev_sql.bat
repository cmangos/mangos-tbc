@echo off
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0run_dev_sql.ps1" %*
pause
