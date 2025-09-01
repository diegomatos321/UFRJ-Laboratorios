@echo off
setlocal enabledelayedexpansion

set TEST_DIR=tests
set RESULTS_DIR=results
set COMPILER=lua.bat compilador.lua
set VM=lua.bat vm.lua

for %%F in ("%TEST_DIR%\*") do (
    echo Compiling: %%F
    CALL %COMPILER% < %%F > "%RESULTS_DIR%\%%~nF.bytecode"
)

for %%F in ("%RESULTS_DIR%\*") do (
    echo Running: %%F
    CALL %VM% %%F > "%RESULTS_DIR%\%%~nF.txt"
)

echo All tests passed successfully!
