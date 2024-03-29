#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include <locale.h>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 2)
    {
        wprintf(L"Argumento para tamanho dos vetores é obrigatório.");
        return EXIT_FAILURE;
    }
    
    const int TAM_VETOR = atoi(argv[1]);
    if (TAM_VETOR < 1)
    {
        wprintf(L"Tamanho do vetor deve ser pelo menos 1.");
        return EXIT_FAILURE;
    }

    printf("%d\n", TAM_VETOR);
    
    srand(time(NULL));
    
    const float MIN_VALUE = -10000.0, MAX_VALUE = 10000.0;
    float soma = 0.0;
    for (int i = 0; i < TAM_VETOR; i++)
    {
        const float scale = rand() / (float) RAND_MAX;
        const float randNumber = MIN_VALUE + scale * (MAX_VALUE - MIN_VALUE);
        soma += randNumber;
        printf("%f ", randNumber);
    }

    printf("\n%f\n", soma);

    return EXIT_SUCCESS;
}
