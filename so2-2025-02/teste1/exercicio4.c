/*
    As funções lstat não funcionam no Windows
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nome_arquivo>\n", argv[0]);
        return 1;
    }

    char *linkpath = argv[1];
    struct stat st;

    // Usando stat() → segue o link
    if (stat(linkpath, &st) == 0)
    {
        printf("stat(\"%s\"): tamanho do alvo = %lld bytes\n", linkpath, (long long)st.st_size);
    }
    else
    {
        perror("stat");
    }

    // Usando lstat() → informações do link em si
    if (lstat(linkpath, &st) == 0)
    {
        printf("lstat(\"%s\"): tamanho do link = %lld bytes\n", linkpath, (long long)st.st_size);
    }
    else
    {
        perror("lstat");
    }

    return 0;
}
