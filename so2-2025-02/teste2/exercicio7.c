#include <stdio.h>    // printf(), fprintf()
#include <stdlib.h>   // EXIT_SUCCESS, EXIT_FAILURE
#include <time.h>     // time(), localtime(), strftime()
#include <string.h>   // snprintf(), strerror()
#include <sys/stat.h> // mkdir()
#include <errno.h>    // errno

int main(int argc, char *argv[])
{
    const char *base_path = "/tmp"; // caminho padrão

    if (argc == 2)
    {
        base_path = argv[1]; // permite passar outro caminho
    }

    // obtém data atual
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    if (!tm_info)
    {
        perror("Erro em localtime");
        return EXIT_FAILURE;
    }

    char date[16]; // espaço suficiente para "YYYY-MM-DD"
    if (strftime(date, sizeof(date), "%Y-%m-%d", tm_info) == 0)
    {
        fprintf(stderr, "Erro ao formatar data\n");
        return EXIT_FAILURE;
    }

    // monta caminho final
    char fullpath[4096];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", base_path, date);

    // cria diretório
    if (mkdir(fullpath, 0755) == -1)
    {
        if (errno == EEXIST)
        {
            printf("Diretório já existe: %s\n", fullpath);
        }
        else
        {
            fprintf(stderr, "Erro ao criar '%s': %s\n", fullpath, strerror(errno));
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("Diretório criado: %s\n", fullpath);
    }

    return EXIT_SUCCESS;
}
