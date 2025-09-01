@echo off
setlocal enabledelayedexpansion

set TEST_DIR=tests
set LUA_PROGRAM=lua.bat compilador.lua

for %%F in ("%TEST_DIR%\*") do (
    echo Running test: %%F
    CALL %LUA_PROGRAM% < %%F
    if errorlevel 1 (
        echo Error encountered in test "%%F" with exit code: !errorlevel!
        exit /b !errorlevel!
    )
)

echo All tests passed successfully!
