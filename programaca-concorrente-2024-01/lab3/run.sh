gcc -c commons/Matriz.c -I commons/
gcc gera-matriz.c Matriz.o -I . -o gera-matriz
gcc matvet-sequencial.c Matriz.o -I . -o matvet-sequencial
gcc matvet-concorrente.c Matriz.o -I . -o matvet-concorrente

./gera-matriz 500 500 data/matriz-500-500.bin
./matvet-sequencial data/matriz-500-500.bin data/matriz-500-500.bin data/resultados/resultado-matvet-sequencial-500-500.bin
./matvet-concorrente data/matriz-500-500.bin data/matriz-500-500.bin data/resultados/resultado-matvet-concorrente-500-500.bin 4