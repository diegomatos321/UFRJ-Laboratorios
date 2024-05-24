#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 3)
    {
        printf("Usage: ./gera-numero <quantidade> <nome_arquivo_saida>\n");
        return EXIT_FAILURE;
    }

    const int N = atoi(argv[1]);
    const char* fileName = argv[2];

    int* buffer = (int*) malloc(sizeof(int) * N);
    if (buffer == NULL)
    {
        printf("Erro ao alocar memória para o buffer");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    static const int MIN_VALUE = -1000, MAX_VALUE = 1000;
    for (int i = 0; i < N; i++)
    {
        const float scale = rand() / (float)RAND_MAX;
        const float randNumber = MIN_VALUE + scale * (MAX_VALUE - MIN_VALUE);

        buffer[i] = randNumber;
    }

    FILE *arquivoSaida = fopen(fileName, "wb");
    if (arquivoSaida == NULL)
    {
        printf("Erro de abertura do arquivo de saída.\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&N, sizeof(int), 1, arquivoSaida);
    fwrite(buffer, sizeof(int), N, arquivoSaida);
    fclose(arquivoSaida);
    
    return EXIT_SUCCESS;
}