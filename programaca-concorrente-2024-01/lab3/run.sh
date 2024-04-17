#!/bin/bash

# Compilando os programas
gcc src/gera-matriz.c src/commons/Matriz.c -I src/commons/ -o build/gera-matriz -Wall
gcc src/matvet-sequencial.c src/commons/Matriz.c -I src/commons/ -o build/matvet-sequencial -Wall
gcc src/matvet-concorrente.c src/commons/Matriz.c -I src/commons/ -o build/matvet-concorrente -Wall -lpthread

# Argumentos que o script irá usar
argumentsA=(500 "data/matriz-500-500.bin" "data/resultados/resultado-matvet-sequencial-500-500.bin" "data/resultados/resultado-matvet-concorrente-500-500.bin")
argumentsB=(1000 "data/matriz-1000-1000.bin" "data/resultados/resultado-matvet-sequencial-1000-1000.bin" "data/resultados/resultado-matvet-concorrente-1000-1000.bin")
argumentsC=(2000 "data/matriz-2000-2000.bin" "data/resultados/resultado-matvet-sequencial-2000-2000.bin" "data/resultados/resultado-matvet-concorrente-2000-2000.bin")

./build/gera-matriz "${argumentsA[0]}" "${argumentsA[0]}" "${argumentsA[1]}"
./build/gera-matriz "${argumentsB[0]}" "${argumentsB[0]}" "${argumentsB[1]}"
./build/gera-matriz "${argumentsC[0]}" "${argumentsC[0]}" "${argumentsC[1]}"

echo "tempo,threads,tamanho"

for i in {1..3}; do
    ./build/matvet-sequencial "${argumentsA[1]}" "${argumentsA[1]}" "${argumentsA[2]}"
done

# Iterando sobre os diferentes números de threads
for nThread in 1 2 4 8; do
    # echo "Gerando resultados para Matriz com $nThread threads..."

    for i in {1..3}; do
        ./build/matvet-concorrente "${argumentsA[1]}" "${argumentsA[1]}" "${argumentsA[3]}" "$nThread"
    done
done

for i in {1..3}; do
    ./build/matvet-sequencial "${argumentsB[1]}" "${argumentsB[1]}" "${argumentsB[2]}"
done

# Iterando sobre os diferentes números de threads
for nThread in 1 2 4 8; do
    # echo "Gerando resultados para Matriz com $nThread threads..."

    for i in {1..3}; do
        ./build/matvet-concorrente "${argumentsB[1]}" "${argumentsB[1]}" "${argumentsB[3]}" "$nThread"
    done
done

for i in {1..3}; do
    ./build/matvet-sequencial "${argumentsC[1]}" "${argumentsC[1]}" "${argumentsC[2]}"
done

# Iterando sobre os diferentes números de threads
for nThread in 1 2 4 8; do
    # echo "Gerando resultados para Matriz com $nThread threads..."

    for i in {1..3}; do
        ./build/matvet-concorrente "${argumentsC[1]}" "${argumentsC[1]}" "${argumentsC[3]}" "$nThread"
    done
done
