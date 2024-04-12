/** 
 * Função responsável por gerar uma matriz de números aleatórios.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include <locale.h>

#include "headers/gera-vetor.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 4)
    {
        wprintf(L"É obrigatórios os argumentos de <linhas>, <colunas> e <nome do arquivo de saída>.\n");
        return EXIT_FAILURE;
    }
    
    int nLinhas, nColunas;
    ReadArguments(argv, &nLinhas, &nColunas);

    const int TAM_VETOR = nLinhas * nColunas;
    float* A = (float*) malloc(sizeof(float) * TAM_VETOR);
    if (A == NULL)
    {
        wprintf(L"Erro ao alocar memória para matriz.\n");
        return EXIT_FAILURE;
    }
    
    GenerateRandMatrix(TAM_VETOR, A);
    WriteToFile(nLinhas, nColunas, TAM_VETOR, A, argv[3]);

    free(A);

    return EXIT_SUCCESS;
}

void ReadArguments(char* argv[], int* nLinhas, int* nColunas) {
    *nLinhas = atoi(argv[1]);
    *nColunas = atoi(argv[2]);
    if (*nLinhas < 1 || *nColunas < 1)
    {
        wprintf(L"As dimensões do vetor devem ser pelo menos 1.\n");
        exit(EXIT_FAILURE);
    }
}

void GenerateRandMatrix(const int TAM_VETOR, float *A)
{
    wprintf(L"Gerando matriz:\n");

    srand(time(NULL));
    static const float MIN_VALUE = -1000.0, MAX_VALUE = 1000.0;
    for (int i = 0; i < TAM_VETOR; i++)
    {
        const float scale = rand() / (float)RAND_MAX;
        const float randNumber = MIN_VALUE + scale * (MAX_VALUE - MIN_VALUE);

        printf("%f ", randNumber);
        A[i] = randNumber;
    }
    
    printf("\n");
}

void WriteToFile(const int nLinhas, const int nColunas, const int TAM_VETOR, float *A, char* fileName) {
    FILE * arquivoSaida = fopen(fileName, "wb");
    if(arquivoSaida == NULL) {
        wprintf(L"Erro de abertura do arquivo de saída.\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&nLinhas, sizeof(int), 1, arquivoSaida);
    fwrite(&nColunas, sizeof(int), 1, arquivoSaida);
    fwrite(A, sizeof(float), TAM_VETOR, arquivoSaida);

    fclose(arquivoSaida);
}