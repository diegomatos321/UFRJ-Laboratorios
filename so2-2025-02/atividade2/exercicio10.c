#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#define PATH_MAX_LEN 4096

void list_dir(const char *path)
{
    char cwd[PATH_MAX_LEN];

    if (chdir(path) == -1)
    {
        fprintf(stderr, "Erro ao entrar em '%s': %s\n", path, strerror(errno));
        return;
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        fprintf(stderr, "Erro em getcwd: %s\n", strerror(errno));
        return;
    }

    printf("Diretório atual: %s\n", cwd);

    DIR *dir = opendir(".");
    if (!dir)
    {
        fprintf(stderr, "Erro ao abrir '%s': %s\n", cwd, strerror(errno));
        return;
    }

    struct dirent *entry;
    printf("Conteúdo:\n");
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0)
        {
            printf("  %s\n", entry->d_name);
        }
    }
    closedir(dir);

    if (chdir("..") == -1)
    {
        fprintf(stderr, "Erro ao voltar de '%s': %s\n", cwd, strerror(errno));
    }
}

int main()
{
    const char *base = "/tmp/temp_test";

    // cria diretório base
    if (mkdir(base, 0755) == -1 && errno != EEXIST)
    {
        fprintf(stderr, "Erro ao criar '%s': %s\n", base, strerror(errno));
        return EXIT_FAILURE;
    }

    // cria subdiretórios
    char sub1[PATH_MAX_LEN], sub2[PATH_MAX_LEN];
    snprintf(sub1, sizeof(sub1), "%s/sub1", base);
    snprintf(sub2, sizeof(sub2), "%s/sub2", base);

    mkdir(sub1, 0755);
    mkdir(sub2, 0755);

    // operações: listagem e chdir
    list_dir(base);
    list_dir(sub1);
    list_dir(sub2);

    // remove subdiretórios
    if (rmdir(sub1) == -1)
        fprintf(stderr, "Erro ao remover '%s': %s\n", sub1, strerror(errno));
    if (rmdir(sub2) == -1)
        fprintf(stderr, "Erro ao remover '%s': %s\n", sub2, strerror(errno));

    // remove diretório base
    if (rmdir(base) == -1)
        fprintf(stderr, "Erro ao remover '%s': %s\n", base, strerror(errno));
    else
        printf("Estrutura temporária removida com sucesso.\n");

    return EXIT_SUCCESS;
}
