@echo off

echo tempo,threads,tamanho

rem Gerando resultados para Matriz 500x500 sequencial...
for /l %%i in (1,1,3) do (    
    @REM echo Loop %%i

    matvet-sequencial.exe .\data\matriz-500-500.bin .\data\matriz-500-500.bin .\data\resultados\resultado-matvet-sequencial-500-500.bin

    @REM echo.
)

rem Iterando sobre os diferentes números de threads
for %%n in (1 2 4 8) do (
    @REM echo Gerando resultados para Matriz 500x500 concorrente com %%n threads...

    for /l %%i in (1,1,3) do (
        matvet-concorrente.exe .\data\matriz-500-500.bin .\data\matriz-500-500.bin .\data\resultados\resultado-matvet-concorrente-500-500.bin %%n

        @REM echo.
    )
)

@REM echo Gerando resultados para Matriz 1000x1000 sequencial...
for /l %%i in (1,1,3) do (    
    @REM echo Loop %%i

    matvet-sequencial.exe .\data\matriz-1000-1000.bin .\data\matriz-1000-1000.bin .\data\resultados\resultado-matvet-sequencial-1000-1000.bin

    @REM echo.
)

rem Iterando sobre os diferentes números de threads
for %%n in (1 2 4 8) do (
    @REM echo Gerando resultados para Matriz 1000x1000 concorrente com %%n threads...

    for /l %%i in (1,1,3) do (    
        @REM echo Loop %%i.

        matvet-concorrente.exe .\data\matriz-1000-1000.bin .\data\matriz-1000-1000.bin .\data\resultados\resultado-matvet-concorrente-1000-1000.bin %%n

        @REM echo.
    )
)

@REM echo Gerando resultados para Matriz 2000x2000 sequencial...
for /l %%i in (1,1,3) do (    
    @REM echo Loop %%i

    matvet-sequencial.exe .\data\matriz-2000-2000.bin .\data\matriz-2000-2000.bin .\data\resultados\resultado-matvet-sequencial-2000-2000.bin

    @REM echo.
)

rem Iterando sobre os valores 1, 2, 4 e 8
for %%n in (1 2 4 8) do (
    @REM echo Gerando resultados para Matriz 2000x2000 concorrente com %%n threads...

    for /l %%i in (1,1,3) do (    
        @REM echo Loop %%i.
        
        matvet-concorrente.exe .\data\matriz-2000-2000.bin .\data\matriz-2000-2000.bin .\data\resultados\resultado-matvet-concorrente-2000-2000.bin %%n

        @REM echo.
    )
)

@REM echo Rotinas concluidas
pause
