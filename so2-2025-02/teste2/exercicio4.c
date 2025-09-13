#include <stdio.h>     // printf(), fprintf()
#include <stdlib.h>    // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>    // strcpy(), strtok(), strlen()
#include <sys/stat.h>  // mkdir()
#include <sys/types.h> // mode_t
#include <errno.h>     // errno, strerror()

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <caminho>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *path = argv[1];
    char temp[4096]; // buffer para construir o caminho parcial
    size_t len = strlen(path);

    if (len >= sizeof(temp))
    {
        fprintf(stderr, "Erro: caminho muito longo.\n");
        return EXIT_FAILURE;
    }

    strcpy(temp, path);

    // percorre a string e cria diretórios ao encontrar '/'
    for (int i = 0; i < len; i++)
    {
        if (temp[i] == '/')
        {
            temp[i] = '\0'; // termina a string aqui
            if (mkdir(temp, 0755) == -1 && errno != EEXIST)
            {
                fprintf(stderr, "Erro ao criar '%s': %s\n", temp, strerror(errno));
                return EXIT_FAILURE;
            }
            temp[i] = '/'; // restaura a barra
        }
    }

    // cria o último diretório
    if (mkdir(temp, 0755) == -1 && errno != EEXIST)
    {
        fprintf(stderr, "Erro ao criar '%s': %s\n", temp, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Diretórios criados com sucesso: %s\n", path);
    return EXIT_SUCCESS;
}
