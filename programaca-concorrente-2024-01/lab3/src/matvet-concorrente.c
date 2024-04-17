#include "matvet-concorrente.h"

// Variáveis em memória compartilhada
int nThreads;
Matriz *A, *B, *C;

// Desconmente para imprimir a matriz.
// #define TEXTO 

// Comente para não imprimir o tempo de produto matricial em formato 
// csv: tempo, threads, tamanho.
#define TO_CSV

/* Função concorrente que será executado por cada thread, responsável por realizar o produto
 * matricial de forma alternada entre as threads e salva o resultado na variável C.
 * 
*/
void* MultiplyMatrices(void *arg)
{
   if (A->cols != B->rows)
   {
      wprintf(L"ERRO: Dimensões não batem.");
      pthread_exit(NULL);
      return NULL;
   }  

   long long int startIndex = (long long int)arg;
   for (int i = startIndex; i < C->rows; i += nThreads)
   {
      for (int j = 0; j < C->cols; j++)
      {
         C->elements[i * C->cols + j] = 0;
         for (int k = 0; k < A->cols; k++)
         {
            C->elements[i * C->cols + j] += A->elements[i * A->cols + k] * B->elements[k * B->cols + j];
         }
      }
   }

   pthread_exit(NULL);
   return NULL;
}

int main(int argc, char *argv[])
{
   setlocale(LC_ALL, "");

   double start, end, delta;

   GET_TIME(start);

   if (argc < 5)
   {
      wprintf(L"Argumentos obrigatórios: <matriz_a.bin> <matriz_b.bin> <arquivo_saída.bin> <nThreads>.\n");
      return EXIT_FAILURE;
   }

   A = ReadMatrix(argv[1]);
   B = ReadMatrix(argv[2]);
   C = CreateMatrix(A->rows, B->cols);

   GET_TIME(end);
   delta = end - start;
   #if !defined(TO_CSV)
   wprintf(L"Tempo inicializacao: %lf\n", delta);
   #endif

   GET_TIME(start);

   nThreads = atoi(argv[4]);
   pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * nThreads);
   for (long long int i = 0; i < nThreads; i++)
   {
      pthread_create(tid + i, NULL, MultiplyMatrices, (void *)i);
   }

   for (int i = 0; i < nThreads; i++)
   {
      pthread_join(tid[i], NULL);
   }

   GET_TIME(end)
   delta = end - start;
   #ifdef TO_CSV
   printf("\"%lf\",%d,%dx%d\n", delta, nThreads, C->rows, C->cols);
   #else
   wprintf(L"Tempo multiplicação das matrizes: %lf\n", delta);
   #endif

   #ifdef TEXTO
   PrintMatrix(C, rowsA, colsB);
   #endif

   WriteMatrixToBinary(C, argv[3]);

   // liberacao da memoria
   GET_TIME(start);
   FreeMatrix(A);
   FreeMatrix(B);
   FreeMatrix(C);
   free(tid);
   GET_TIME(end)
   delta = end - start;
   #if !defined(TO_CSV)
   printf("Tempo finalizacao: %lf\n", delta);
   #endif

   return EXIT_SUCCESS;
}
