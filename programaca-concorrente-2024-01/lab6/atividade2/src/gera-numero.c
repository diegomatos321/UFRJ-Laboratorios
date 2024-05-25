#include "gera-numero.h"

int main(int argc, char* argv[]) {
    if (argc < 3)
    {
        printf("Usage: ./gera-numero <tamanho> <nome_arquivo_saida (sem extensao)>\n");
        return EXIT_FAILURE;
    }

    const unsigned int N = atoi(argv[1]);
    const char* inputFilename = argv[2];

    int* buffer = (int*) malloc(sizeof(int) * N);
    if (buffer == NULL)
    {
        printf("Erro ao alocar memória para o buffer");
        return EXIT_FAILURE;
    }

    time_t t;
    srand((unsigned) time(&t));
    const int MIN_VALUE = -1000, MAX_VALUE = 1000;
    unsigned int quantidade_primos = 0;
    // Gera um número inteiro aleatório entre min e max
    for (unsigned int i = 0; i < N; i++)
    {
        const double scale = rand() / (double) RAND_MAX;
        int randNumber = MIN_VALUE + scale * (MAX_VALUE - MIN_VALUE);

        buffer[i] = randNumber;
        // printf("%d, ", randNumber);

        if (ehPrimo(randNumber))
            quantidade_primos++;
    }

    // Salva lista de inteiros em arquivo binário
    char* fileName = concat(inputFilename, ".bin");
    FILE *arquivoSaida = fopen(fileName, "wb");
    if (arquivoSaida == NULL)
    {
        printf("Erro de abertura do arquivo de saída.\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&N, sizeof(unsigned int), 1, arquivoSaida);
    fwrite(buffer, sizeof(int), N, arquivoSaida);
    fclose(arquivoSaida);
    free(fileName);

    // Salva em um arquivo de texto a quantidade de números primos
    char* testFilename = concat(inputFilename, "_test.txt");
    FILE *arquivoTest = fopen(testFilename, "w");
    if (arquivoTest == NULL)
    {
        printf("Erro de abertura do arquivo de teste.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivoTest, "%d\n", quantidade_primos);
    fclose(arquivoTest);
    free(testFilename);

    free(buffer);

    return EXIT_SUCCESS;
}


