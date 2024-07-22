@echo off

@REM Compilar o código usando gcc
gcc src\main.c -o build\main.exe -Wall -lpthread -lm

@REM Definir os valores de N
set valores_N=1000 1000000 10000000

@REM Loop para cada valor de N
for %%N in (%valores_N%) do (
    @REM Loop para cada número de threads
    for %%j in (1,2,4,8) do (
        @REM Loop para executar o programa 5 vezes
        for /l %%i in (1,1,5) do (
            build\main.exe %%N %%j
        )
    )
)
