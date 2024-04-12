#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "timer.h"

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

void MultiplyMatrices(float *A, float *B, int rowsA, int colsA, int colsB, float *C)
{
   const int rowsC = rowsA;
   const int colsC = colsB;

   for (int i = 0; i < rowsC; ++i)
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

   int rowsA, colsA, rowsB, colsB;
   double start, end, delta;
   float *A, *B, *C;

   GET_TIME(start);

   if (argc < 4)
   {
      wprintf(L"Argumentos obrigatórios: <matriz_a> <matriz_b> <arquivo saída>.\n");
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
   wprintf(L"Tempo inicializacao: %lf\n", delta);

   GET_TIME(start);

   MultiplyMatrices(A, B, rowsA, colsA, colsB, C);

   GET_TIME(end)
   delta = end - start;
   wprintf(L"Tempo multiplicação das matrizes: %lf\n", delta);

   PrintMatrix(C, rowsA, colsB);

   // liberacao da memoria
   GET_TIME(start);
   free(A);
   free(B);
   free(C);
   GET_TIME(end)
   delta = end - start;
   printf("Tempo finalizacao: %lf\n", delta);

   return EXIT_SUCCESS;
}
