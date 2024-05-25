@echo off
setlocal

REM Caminho para a instalação do vcpkg
set VCPKG_PATH="D:/Programas/vcpkg"

REM Compilar e linkar
cl -W4 src/gera-numero.c src/include/ehprimo.c src/include/concat.c -I"src/include/" -Fo"bin/" -link -out:"bin/gera-numero.exe"
cl -W4 -MT src/main.c src/include/ehprimo.c src/include/concat.c -I"src/include/" -I"%VCPKG_PATH%/installed/x64-windows-static/include" -Fo"bin/" -link -LIBPATH:"%VCPKG_PATH%/installed/x64-windows-static/lib" pthreadVC3.lib -out:"bin/produtor-consumidor.exe"
endlocal
