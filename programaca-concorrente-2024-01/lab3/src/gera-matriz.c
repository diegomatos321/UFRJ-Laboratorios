/** 
 * Função responsável por gerar uma matriz de números aleatórios.
 * 
 */

#include "gera-matriz.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 4)
    {
        wprintf(L"É obrigatórios os argumentos de <número_linhas>, <número_colunas> e <nome_do_arquivo_de_saída>.\n");
        return EXIT_FAILURE;
    }
    
    int rows, cols;
    ReadArguments(argv, &rows, &cols);

    Matriz *A = GenerateRandMatrix(rows, cols);
    WriteMatrixToBinary(A, argv[3]);

    FreeMatrix(A);

    return EXIT_SUCCESS;
}

void ReadArguments(char *argv[], int *rows, int *cols) {
    *rows = atoi(argv[1]);
    *cols = atoi(argv[2]);
    if (*rows < 1 || *cols < 1)
    {
        wprintf(L"As dimensões do vetor devem ser pelo menos 1.\n");
        exit(EXIT_FAILURE);
    }
}

Matriz* GenerateRandMatrix(const int rows, const int cols)
{
    Matriz *A = CreateMatrix(rows, cols);

    srand(time(NULL));
    static const float MIN_VALUE = -1000.0, MAX_VALUE = 1000.0;
    for (int i = 0; i < A->rows * A->cols; i++)
    {
        const float scale = rand() / (float)RAND_MAX;
        const float randNumber = MIN_VALUE + scale * (MAX_VALUE - MIN_VALUE);

        A->elements[i] = randNumber;
    }

    return A;
}
