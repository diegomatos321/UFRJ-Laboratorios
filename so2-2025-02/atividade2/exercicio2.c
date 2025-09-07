#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> // para rmdir()

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
        if (rmdir(dir) == -1)
        {
            fprintf(stderr, "Erro ao remover '%s': %s\n", dir, strerror(errno));
        }
        else
        {
            printf("Diretório removido: %s\n", dir);
        }
    }

    return EXIT_SUCCESS;
}
