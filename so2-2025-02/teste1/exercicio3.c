/*
    Conseguimos escrever um programa esquivalente no windows
    usando _stat
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void mostra_permissoes(unsigned short mode)
{
    char perm[10];

    perm[0] = (mode & _S_IREAD) ? 'r' : '-';
    perm[1] = (mode & _S_IWRITE) ? 'w' : '-';
    perm[2] = (mode & _S_IEXEC) ? 'x' : '-';
    // Em Windows não há distinção clara entre grupo/outros, repetimos:
    perm[3] = perm[0];
    perm[4] = perm[1];
    perm[5] = perm[2];
    perm[6] = perm[0];
    perm[7] = perm[1];
    perm[8] = perm[2];
    perm[9] = '\0';

    printf("Permissoes: %s\n", perm);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nome_arquivo>\n", argv[0]);
        return 1;
    }

    struct _stat st;
    if (_stat(argv[1], &st) != 0)
    {
        perror("Erro ao obter informacoes do arquivo");
        return 1;
    }

    printf("Arquivo: %s\n", argv[1]);
    printf("Tamanho: %lld bytes\n", (long long)st.st_size);
    printf("Numero de links: %lu\n", (unsigned long)st.st_nlink);
    printf("UID do dono: (nao disponivel no Windows)\n");

    mostra_permissoes(st.st_mode);

    char buffer[80];
    struct tm tm_info;
    localtime_s(&tm_info, &st.st_mtime);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", &tm_info);
    printf("Ultima modificacao: %s\n", buffer);

    return 0;
}
