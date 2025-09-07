#include <stdio.h>  // printf(), fprintf()
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> // strerror()
#include <errno.h>  // errno
#include <unistd.h> // rmdir()
#include <dirent.h> // opendir(), readdir(), closedir()

int is_dir_empty(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        perror("Erro ao abrir diretório");
        return -1; // erro
    }

    struct dirent *entry;
    int empty = 1; // assume vazio

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0)
        {
            empty = 0; // achou algum arquivo
            break;
        }
    }

    closedir(dir);
    return empty;
}

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
        int res = is_dir_empty(dir);

        if (res == -1)
        {
            fprintf(stderr, "Não foi possível verificar '%s'\n", dir);
            continue;
        }

        if (!res)
        {
            printf("Diretório não vazio: %s\n", dir);
            continue;
        }

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
