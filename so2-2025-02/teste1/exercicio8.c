#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void mostra_tipo(mode_t mode)
{
    if (S_ISREG(mode))
        printf("regular");
    else if (S_ISDIR(mode))
        printf("diretório");
    else if (S_ISLNK(mode))
        printf("link simbólico");
    else if (S_ISCHR(mode))
        printf("dispositivo de caractere");
    else if (S_ISBLK(mode))
        printf("dispositivo de bloco");
    else if (S_ISFIFO(mode))
        printf("pipe (FIFO)");
    else if (S_ISSOCK(mode))
        printf("socket");
    else
        printf("desconhecido");
}

void mostra_permissoes(mode_t mode)
{
    char perm[10];

    perm[0] = (mode & S_IRUSR) ? 'r' : '-';
    perm[1] = (mode & S_IWUSR) ? 'w' : '-';
    perm[2] = (mode & S_IXUSR) ? 'x' : '-';
    perm[3] = (mode & S_IRGRP) ? 'r' : '-';
    perm[4] = (mode & S_IWGRP) ? 'w' : '-';
    perm[5] = (mode & S_IXGRP) ? 'x' : '-';
    perm[6] = (mode & S_IROTH) ? 'r' : '-';
    perm[7] = (mode & S_IWOTH) ? 'w' : '-';
    perm[8] = (mode & S_IXOTH) ? 'x' : '-';
    perm[9] = '\0';

    printf("permissões: %s", perm);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Uso: %s <arquivo1> <arquivo2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        struct stat st;
        if (lstat(argv[i], &st) != 0)
        {
            perror(argv[i]);
            continue;
        }

        printf("\nArquivo: %s\n", argv[i]);
        printf("tamanho: %lld bytes\n", (long long)st.st_size);
        printf("tipo: ");
        mostra_tipo(st.st_mode);
        printf("\n");
        mostra_permissoes(st.st_mode);
        printf("\n");
    }

    return 0;
}
