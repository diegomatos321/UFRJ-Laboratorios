#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <locale.h>
#include <wchar.h>
#include "timer.h"

// Variáveis em memória compartilhada
int rowsA, colsA, rowsB, colsB, nThreads;
float *A, *B, *C;

// #define TEXTO 
#define TO_CSV

FILE* ReadDimensions(const char* fileName, int *rows, int *cols)
{
   FILE *file = fopen(fileName, "rb");
   if (file == NULL)
   {
      wprintf(L"Erro de abertura do arquivo de entrada.\n");
      exit(EXIT_FAILURE);
   }

   fread(rows, sizeof(int), 1, file);
   fread(cols, sizeof(int), 1, file);

   return file;
}

void ReadMatrix(FILE *file, float *matrix, int tam)
{
   fread(matrix, sizeof(float), tam, file);
}

void* MultiplyMatrices(void *arg)
{
   long long int startIndex = (long long int)arg;
   const int rowsC = rowsA;
   const int colsC = colsB;

   // TODO: Verificar se o tamanho do passo não excede o tamanho do vetor
   for (int i = startIndex; i < rowsC; i += nThreads)
   {
      for (int j = 0; j < colsC; j++)
      {
         C[i * colsC + j] = 0;
         for (int k = 0; k < colsA; k++)
         {
            C[i * colsC + j] += A[i * colsA + k] * B[k * colsB + j];
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

void WriteToFile(char* fileName, const int nLinhas, const int nColunas, const int TAM_VETOR, float *matriz) {
      FILE * arquivoSaida = fopen(fileName, "wb");
      if(arquivoSaida == NULL) {
         wprintf(L"Erro de abertura do arquivo de saída.\n");
         exit(EXIT_FAILURE);
      }
   
      fwrite(&nLinhas, sizeof(int), 1, arquivoSaida);
      fwrite(&nColunas, sizeof(int), 1, arquivoSaida);
      fwrite(matriz, sizeof(float), TAM_VETOR, arquivoSaida);
}

int main(int argc, char *argv[])
{
   setlocale(LC_ALL, "");

   double start, end, delta;

   GET_TIME(start);

   if (argc < 5)
   {
      wprintf(L"Argumentos obrigatórios: <matriz_a> <matriz_b> <arquivo saída> <nThreads>.\n");
      return EXIT_FAILURE;
   }

   FILE *fileA = ReadDimensions(argv[1], &rowsA, &colsA);
   FILE *fileB = ReadDimensions(argv[2], &rowsB, &colsB);

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

   ReadMatrix(fileA, A, TAM_VETOR_A);
   ReadMatrix(fileB, B, TAM_VETOR_B);

   fclose(fileA);
   fclose(fileB);

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
   printf("\"%lf\",%d,%dx%d\n", delta, nThreads, rowsA, colsB);
   #else
   wprintf(L"Tempo multiplicação das matrizes: %lf\n", delta);
   #endif

   #ifdef TEXTO
   PrintMatrix(C, rowsA, colsB);
   #endif

   WriteToFile(argv[3], rowsA, colsB, TAM_VETOR_C, C);

   // liberacao da memoria
   GET_TIME(start);
   free(A);
   free(B);
   free(C);
   free(tid);
   GET_TIME(end)
   delta = end - start;
   #if !defined(TO_CSV)
   printf("Tempo finalizacao: %lf\n", delta);
   #endif

   return EXIT_SUCCESS;
}
