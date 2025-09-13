#include <stdio.h>    // printf(), fprintf()
#include <stdlib.h>   // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>   // strcmp(), strerror()
#include <unistd.h>   // chdir(), getcwd()
#include <dirent.h>   // opendir(), readdir(), closedir()
#include <errno.h>    // errno
#include <sys/stat.h> // stat(), S_ISDIR

#define PATH_MAX_LEN 4096

void list_dirs(const char *path)
{
    char cwd[PATH_MAX_LEN];

    // tenta entrar no diretório
    if (chdir(path) == -1)
    {
        fprintf(stderr, "Erro ao entrar em '%s': %s\n", path, strerror(errno));
        return;
    }

    // obtém e imprime diretório atual
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        fprintf(stderr, "Erro em getcwd: %s\n", strerror(errno));
        return;
    }
    printf("%s\n", cwd);

    // abre diretório
    DIR *dir = opendir(".");
    if (!dir)
    {
        fprintf(stderr, "Erro ao abrir diretório '%s': %s\n", cwd, strerror(errno));
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // ignora "." e ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        // verifica se é diretório
        struct stat st;
        if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode))
        {
            // chamada recursiva
            list_dirs(entry->d_name);
        }
    }

    closedir(dir);

    // volta para diretório pai
    if (chdir("..") == -1)
    {
        fprintf(stderr, "Erro ao voltar de '%s': %s\n", cwd, strerror(errno));
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <caminho>\n", argv[0]);
        return EXIT_FAILURE;
    }

    list_dirs(argv[1]);

    return EXIT_SUCCESS;
}
