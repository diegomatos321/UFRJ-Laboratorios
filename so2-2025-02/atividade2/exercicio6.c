#include <stdio.h>  // printf(), fprintf()
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h> // chdir(), getcwd()
#include <errno.h>  // errno
#include <string.h> // strerror()

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <novo_caminho>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char original[4096];
    if (getcwd(original, sizeof(original)) == NULL)
    {
        fprintf(stderr, "Erro ao obter diretório atual: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Diretório original: %s\n", original);

    const char *novo = argv[1];
    if (chdir(novo) == -1)
    {
        fprintf(stderr, "Erro ao mudar para '%s': %s\n", novo, strerror(errno));
        return EXIT_FAILURE;
    }

    char atual[4096];
    if (getcwd(atual, sizeof(atual)) == NULL)
    {
        fprintf(stderr, "Erro ao obter novo diretório: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Diretório após mudança: %s\n", atual);

    // voltar para o original
    if (chdir(original) == -1)
    {
        fprintf(stderr, "Erro ao voltar para '%s': %s\n", original, strerror(errno));
        return EXIT_FAILURE;
    }

    if (getcwd(atual, sizeof(atual)) == NULL)
    {
        fprintf(stderr, "Erro ao obter diretório restaurado: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Diretório restaurado: %s\n", atual);

    return EXIT_SUCCESS;
}
