#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "timer.h"

// #define TEXTO 
#define TO_CSV

typedef struct {
   int rows;
   int cols;
   float *elements;
} Matriz;

Matriz* CreateMatrix(int rows, int cols) {
   Matriz *result = malloc(sizeof(Matriz));
   if (result == NULL)
   {
      wprintf(L"Erro ao alocar memória para matriz");
      exit(EXIT_FAILURE);
   }
   
   result->rows = rows;
   result->cols = cols;
   result->elements = malloc(sizeof(float) * rows * cols);
   if (result->elements == NULL)
   {
      wprintf(L"Erro ao alocar memória para os dados da matriz");
      free(result);
      exit(EXIT_FAILURE);
   }
   
   return result;
}

void FreeMatrix(Matriz *matrix) {
   free(matrix->elements);
   free(matrix);
}

Matriz* ReadMatrix(const char* fileName) {
   FILE *file = fopen(fileName, "rb");
   if (file == NULL)
   {
      wprintf(L"Erro de abertura do arquivo de entrada.\n");
      exit(EXIT_FAILURE);
   }

   int rows, cols;
   fread(&rows, sizeof(int), 1, file);
   fread(&cols, sizeof(int), 1, file);

   Matriz *result = CreateMatrix(rows, cols);
   fread(result->elements, sizeof(float), rows * cols, file);

   fclose(file);
   return result;
}

Matriz *MultiplyMatrices(Matriz *A, Matriz *B)
{
   if (A->cols != B->cols)
   {
      wprintf(L"Não é possível multiplicar as matrizes: Erro de dimensões");
      exit(EXIT_FAILURE);
   }

   Matriz *C = CreateMatrix(A->rows, B->cols);

   for (int i = 0; i < C->rows; ++i)
   {
      for (int j = 0; j < C->cols; j++)
      {
         C->elements[i * C->cols + j] = 0.0;
         for (int k = 0; k < A->cols; k++)
         {
            C->elements[i * C->cols + j] += A->elements[i * A->cols + k] * B->elements[k * B->cols + j];
         }
      }
   }

   return C;
}

void PrintMatrix(Matriz *matrix)
{
   for (int i = 0; i < matrix->rows; ++i)
   {
      for (int j = 0; j < matrix->cols; ++j)
      {
         printf("%f ", matrix->elements[i * matrix->cols + j]);
      }
      printf("\n");
   }
}

void WriteToFile(Matriz* matrix, char *fileName) {
      FILE * arquivoSaida = fopen(fileName, "wb");
      if(arquivoSaida == NULL) {
         wprintf(L"Erro de abertura do arquivo de saída.\n");
         exit(EXIT_FAILURE);
      }
   
      fwrite(matrix->rows, sizeof(int), 1, arquivoSaida);
      fwrite(matrix->cols, sizeof(int), 1, arquivoSaida);
      fwrite(matrix->elements, sizeof(float), matrix->rows * matrix->cols, arquivoSaida);
}

int main(int argc, char *argv[])
{
   setlocale(LC_ALL, "");

   double start, end, delta;

   GET_TIME(start);

   if (argc < 4)
   {
      wprintf(L"Argumentos obrigatórios: <matriz_a.bin> <matriz_b.bin> <arquivo saída.bin>.\n");
      return EXIT_FAILURE;
   }

   Matriz *A = ReadMatrix(argv[1]);
   Matriz *B = ReadMatrix(argv[2]);

   GET_TIME(end);
   delta = end - start;
   #if !defined(TO_CSV)
   wprintf(L"Tempo inicializacao: %lf\n", delta);
   #endif

   GET_TIME(start);

   Matriz *C = MultiplyMatrices(A, B);

   GET_TIME(end)
   delta = end - start;
   #ifdef TO_CSV
   printf("\"%lf\",,%dx%d\n", delta, C->rows, C->cols); // Tempo, threads em branco e dimensões
   #else
   wprintf(L"Tempo multiplicação das matrizes: %lf\n", delta);
   #endif

   #ifdef TEXTO
   PrintMatrix(C, rowsA, colsB);
   #endif
   
   WriteToFile(C, argv[3]);

   // liberacao da memoria
   GET_TIME(start);
   FreeMatrix(A);
   FreeMatrix(B);
   FreeMatrix(C);
   GET_TIME(end)
   delta = end - start;

   #if !defined(TO_CSV)
   printf("Tempo finalizacao: %lf\n", delta);
   #endif

   return EXIT_SUCCESS;
}
