#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Uso: %s dir1 [dir2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++)
    {
        const char *dir = argv[i];
        if (mkdir(dir, 0755) == -1)
        {
            if (errno == EEXIST)
            {
                fprintf(stderr, "Aviso: diretório '%s' já existe.\n", dir);
            }
            else
            {
                fprintf(stderr, "Erro ao criar '%s': %s\n", dir, strerror(errno));
                return EXIT_FAILURE;
            }
        }
        else
        {
            printf("Diretório criado: %s\n", dir);
        }
    }

    return EXIT_SUCCESS;
}
