#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void mostra_tipo(struct stat *st)
{
    if (S_ISREG(st->st_mode))
    {
        printf("Arquivo regular\n");
    }
    else if (S_ISDIR(st->st_mode))
    {
        printf("Diretório\n");
    }
    else if (S_ISLNK(st->st_mode))
    {
        printf("Link simbólico\n");
    }
    else
    {
        printf("Outro tipo\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Erro ao abrir arquivo");
        return 1;
    }

    struct stat st_fd;
    if (fstat(fd, &st_fd) != 0)
    {
        fprintf(stderr, "Erro em fstat");
        close(fd);
        return 1;
    }

    printf("Resultado de fstat(%s):\n", argv[1]);
    mostra_tipo(&st_fd);

    struct stat st_path;
    if (stat(argv[1], &st_path) != 0)
    {
        fprintf(stderr, "Erro em stat");
        close(fd);
        return 1;
    }

    printf("Resultado de stat(%s):\n", argv[1]);
    mostra_tipo(&st_path);

    // Comparando se são iguais
    if (st_fd.st_ino == st_path.st_ino && st_fd.st_dev == st_path.st_dev)
    {
        printf("fstat e stat retornaram o mesmo objeto.\n");
    }
    else
    {
        printf("fstat e stat retornaram objetos diferentes.\n");
    }

    close(fd);
    return 0;
}
