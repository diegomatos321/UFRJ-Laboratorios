/** 
 * Programa que gera duas matrizes aleatórias A_nxm e B_mx1 e salva
 * num arquivo binário.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include <locale.h>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 4)
    {
        wprintf(L"É obrigatórios os argumentos de linhas, colunas e nome do arquivo de saída.\n");
        return EXIT_FAILURE;
    }
    
    const int nLinhas = atoi(argv[1]);
    const int nColunas = atoi(argv[2]);
    if (nLinhas < 1 || nColunas < 1)
    {
        wprintf(L"As dimensões do vetor devem ser pelo menos 1.\n");
        return EXIT_FAILURE;
    }

    const int TAM_VETOR = nLinhas * nColunas;
    float* A = (float*) malloc(sizeof(float) * TAM_VETOR);
    float* B = (float*) malloc(sizeof(float) * nColunas);
    if (A == NULL || B == NULL)
    {
        wprintf(L"Erro ao alocar memória para matriz.\n");
        return EXIT_FAILURE;
    }
    
    srand(time(NULL));
    
    wprintf(L"Gerando matriz A:\n");
    static const float MIN_VALUE = -10000.0, MAX_VALUE = 10000.0;
    for (int i = 0; i < TAM_VETOR; i++)
    {
        const float scale = rand() / (float) RAND_MAX;
        const float randNumber = MIN_VALUE + scale * (MAX_VALUE - MIN_VALUE);

        printf("%f ", randNumber);
        A[i] = randNumber;
    }
    printf("\n");

    wprintf(L"Gerando matriz B:\n");
    for (int i = 0; i < nColunas; i++)
    {
        const float scale = rand() / (float) RAND_MAX;
        const float randNumber = MIN_VALUE + scale * (MAX_VALUE - MIN_VALUE);
        printf("%f ", randNumber);
        B[i] = randNumber;
    }
    printf("\n");
    
    FILE * arquivoSaida = fopen(argv[3], "wb");
    if(arquivoSaida == NULL) {
        wprintf(L"Erro de abertura do arquivo de saída.\n");
        return EXIT_FAILURE;
    }

    fwrite(&nLinhas, sizeof(int), 1, arquivoSaida);
    fwrite(&nColunas, sizeof(int), 1, arquivoSaida);
    fwrite(&nColunas, sizeof(int), 1, arquivoSaida);
    int tmp = 1;
    fwrite(&tmp, sizeof(int), 1, arquivoSaida);

    fwrite(A, sizeof(float), TAM_VETOR, arquivoSaida);
    fwrite(B, sizeof(int), nColunas, arquivoSaida);

    /* if(ret == NULL) {
        wprintf(L"Erro de escrita no arquivo de saída.\n");
        return EXIT_FAILURE;
    } */

    fclose(arquivoSaida);
    free(A);
    free(B);

    return EXIT_SUCCESS;
}
