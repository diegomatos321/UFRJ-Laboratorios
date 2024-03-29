#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include <locale.h>

float* vetor;

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 2)
    {
        wprintf(L"Argumento para números de threads é obrigatório.");
        return EXIT_FAILURE;
    }

    const int nThreads = atoi(argv[1]);

    int TAM_VETOR;
    scanf("%d", &TAM_VETOR);

    vetor = (float*) malloc(sizeof(float) * TAM_VETOR);
    if (vetor == NULL)
    {
        wprintf(L"Erro ao alocar memória para o vetor.");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < count; i++)
    {
        /* code */
    }
    

    return EXIT_SUCCESS;
}