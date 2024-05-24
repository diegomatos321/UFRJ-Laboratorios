#include "gera-numero.h"

int main(int argc, char* argv[]) {
    if (argc < 3)
    {
        printf("Usage: ./gera-numero <tamanho> <nome_arquivo_saida (sem extensao)>\n");
        return EXIT_FAILURE;
    }

    const int N = atoi(argv[1]);
    const char* inputFilename = argv[2];

    int* buffer = (int*) malloc(sizeof(int) * N);
    if (buffer == NULL)
    {
        printf("Erro ao alocar memória para o buffer");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    static const int MIN_VALUE = -1000, MAX_VALUE = 1000;
    unsigned int quantidade_primos = 0;
    for (int i = 0; i < N; i++)
    {
        const int scale = rand() / RAND_MAX;
        const int randNumber = MIN_VALUE + scale * (MAX_VALUE - MIN_VALUE);

        buffer[i] = randNumber;

        if (ehPrimo(randNumber))
            quantidade_primos++;
    }

    char* fileName = concat(inputFilename, ".bin");
    FILE *arquivoSaida = fopen(fileName, "wb");
    if (arquivoSaida == NULL)
    {
        printf("Erro de abertura do arquivo de saída.\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&N, sizeof(int), 1, arquivoSaida);
    fwrite(buffer, sizeof(int), N, arquivoSaida);
    fclose(arquivoSaida);
    free(arquivoSaida);

    char* testFilename = concat(inputFilename, "_test.bin");
    FILE *arquivoTest = fopen(testFilename, "wb");
    if (arquivoTest == NULL)
    {
        printf("Erro de abertura do arquivo de teste.\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&quantidade_primos, sizeof(unsigned int), 1, arquivoTest);
    fclose(arquivoTest);
    free(arquivoTest);

    free(inputFilename);
    free(testFilename);
    free(fileName);
    free(buffer);

    return EXIT_SUCCESS;
}


