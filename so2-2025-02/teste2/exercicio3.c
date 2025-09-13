#include <stdio.h>  // printf(), fprintf()
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h> // chdir(), getcwd()
#include <errno.h>  // errno (códigos de erro)
#include <string.h> // strerror() (converter errno em mensagem legível)

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <caminho>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *path = argv[1];

    // tenta mudar para o diretório informado
    if (chdir(path) == -1)
    {
        fprintf(stderr, "Erro ao mudar para '%s': %s\n", path, strerror(errno));
        return EXIT_FAILURE;
    }

    // buffer para armazenar o caminho absoluto atual
    char cwd[4096]; // 4096 é comum em sistemas Linux
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        fprintf(stderr, "Erro ao obter diretório atual: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Diretório atual: %s\n", cwd);

    return EXIT_SUCCESS;
}
