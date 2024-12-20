#include "concat.h"

char* concat(const char *s1, const char *s2)
{
    size_t resultLength = strlen(s1) + strlen(s2) + 1;
    char* result = malloc(resultLength); // +1 for the null-terminator
    if (result == NULL)
    {
        printf("Erro ao alocar memória para a concatenação de strings.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}