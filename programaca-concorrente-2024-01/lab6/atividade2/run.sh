gcc src/gera-numero.c src/include/ehprimo.c src/include/concat.c -Wall -I"src/include" -o bin/gera-numero -Wall
gcc src/main.c src/include/ehprimo.c src/include/concat.c -Wall -I"src/include" -lpthread -o bin/gera-numero 
