#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <locale.h>
#include <wchar.h>
#include "timer.h"

// Variáveis em memória compartilhada
int rowsA, colsA, rowsB, colsB, nThreads;
float *A, *B, *C;

void ReadDimensions(FILE *file, int *rows, int *cols)
{
   fread(rows, sizeof(int), 1, file);
   fread(cols, sizeof(int), 1, file);
}

void ReadMatrix(FILE *file, float *matrix, int tam)
{
   fread(matrix, sizeof(float), tam, file);
}

void MultiplyMatrices(void *arg)
{
   int startIndex = (int)arg;

   // TODO: Verificar se o tamanho do passo não excede o tamanho do vetor
   for (int i = startIndex; i < rowsA; i += nThreads)
   {
      for (int j = 0; j < colsB; j++)
      {
         C[i * colsB + j] = 0;
         for (int k = 0; k < colsA; k++)
         {
            C[i * colsB + j] += A[i * colsA + k] * B[k * colsB + j];
         }
      }
   }

   pthread_exit(NULL);
   return NULL;
}

void PrintMatrix(float *matrix, int rows, int cols)
{
   for (int i = 0; i < rows; ++i)
   {
      for (int j = 0; j < cols; ++j)
      {
         printf("%f ", matrix[i * cols + j]);
      }
      printf("\n");
   }
}

int main(int argc, char *argv[])
{
   setlocale(LC_ALL, "");

   double start, end, delta;

   GET_TIME(start);

   if (argc < 4)
   {
      wprintf(L"Argumentos obrigatórios: <arquivo entrada> <arquivo saída> <número de threads>.\n");
      return EXIT_FAILURE;
   }

   FILE *arquivoEntrada = fopen(argv[1], "rb");
   if (arquivoEntrada == NULL)
   {
      wprintf(L"Erro de abertura do arquivo de entrada.\n");
      return EXIT_FAILURE;
   }

   ReadDimensions(arquivoEntrada, &rowsA, &colsA);
   ReadDimensions(arquivoEntrada, &rowsB, &colsB);

   // Verificar dimensões das matrizes
   if (colsA != rowsB)
   {
      wprintf(L"Erro-- As dimensões das matrizes não são válidas.\n");
      return EXIT_FAILURE;
   }

   const int TAM_VETOR_A = rowsA * colsA;
   const int TAM_VETOR_B = rowsB * colsB;
   const int TAM_VETOR_C = rowsA * colsB;

   A = (float *)malloc(sizeof(float) * TAM_VETOR_A);
   B = (float *)malloc(sizeof(float) * TAM_VETOR_B);
   C = (float *)malloc(sizeof(float) * TAM_VETOR_C);
   if (A == NULL || B == NULL || C == NULL)
   {
      wprintf(L"Erro de alocação da memória da matriz.\n");
      return EXIT_FAILURE;
   }

   ReadMatrix(arquivoEntrada, A, TAM_VETOR_A);
   ReadMatrix(arquivoEntrada, B, TAM_VETOR_B);

   fclose(arquivoEntrada);

   GET_TIME(end);
   delta = end - start;
   wprintf(L"Tempo inicializacao: %lf\n", delta);

   GET_TIME(start);

   nThreads = atoi(argv[3]);
   pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * nThreads);
   for (int i = 0; i < nThreads; i++)
   {
      pthread_create(tid + i, NULL, MultiplyMatrices, (void *)i);
   }

   GET_TIME(end)
   delta = end - start;
   wprintf(L"Tempo multiplicação das matrizes: %lf\n", delta);

   PrintMatrix(C, rowsA, colsB);

   // liberacao da memoria
   GET_TIME(start);
   free(A);
   free(B);
   free(C);
   free(tid);
   GET_TIME(end)
   delta = end - start;
   printf("Tempo finalizacao: %lf\n", delta);

   return EXIT_SUCCESS;
}
