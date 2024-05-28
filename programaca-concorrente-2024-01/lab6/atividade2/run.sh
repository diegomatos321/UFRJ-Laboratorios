gcc src/gera-numero.c src/include/ehprimo.c src/include/concat.c -Wall -I"src/include" -lm -o bin/gera-numero
gcc src/main.c src/include/ehprimo.c src/include/concat.c -Wall -I"src/include" -lm -lpthread -o bin/produtor-consumidor
