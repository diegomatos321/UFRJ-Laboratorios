gcc -c src/commons/Matriz.c -I src/commons/ -o build/Matriz.o
gcc src/gera-matriz.c build/Matriz.o -I . -o build/gera-matriz
gcc src/matvet-sequencial.c build/Matriz.o -I . -o build/matvet-sequencial
gcc src/matvet-concorrente.c build/Matriz.o -I . -o build/matvet-concorrente

./build/gera-matriz 500 500 data/matriz-500-500.bin
./build/matvet-sequencial data/matriz-500-500.bin data/matriz-500-500.bin data/resultados/resultado-matvet-sequencial-500-500.bin
./build/matvet-concorrente data/matriz-500-500.bin data/matriz-500-500.bin data/resultados/resultado-matvet-concorrente-500-500.bin 4
