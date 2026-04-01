@echo off
setlocal enabledelayedexpansion

set FILES=
for /r . %%f in (*.cpp) do set FILES=!FILES! "%%f"

g++ -I. -o poker -std=c++17 !FILES!

echo.
echo Build selesai! Jalankan dengan: poker.exe