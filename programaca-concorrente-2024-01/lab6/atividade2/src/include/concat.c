#include "concat.h"

char* concat(const char *s1, const char *s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    if (result == NULL)
    {
        printf("Erro ao alocar memória para a concatenação de strings.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}