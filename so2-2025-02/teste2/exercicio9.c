#include <stdio.h>    // printf(), fprintf()
#include <stdlib.h>   // EXIT_SUCCESS, EXIT_FAILURE
#include <sys/stat.h> // mkdir(), chmod()
#include <errno.h>    // errno
#include <string.h>   // strerror()

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nome_diretorio>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dir = argv[1];

    // cria o diretório com permissões padrão (0755)
    if (mkdir(dir, 0755) == -1)
    {
        fprintf(stderr, "Erro ao criar '%s': %s\n", dir, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Diretório criado: %s\n", dir);

    // altera permissões para rwxr-x--- (0750)
    if (chmod(dir, 0750) == -1)
    {
        fprintf(stderr, "Erro ao alterar permissões de '%s': %s\n", dir, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Permissões alteradas para rwxr-x--- (0750)\n");

    return EXIT_SUCCESS;
}
