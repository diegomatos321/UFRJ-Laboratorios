#include <locale.h>
#include "commons/Matriz.h"
#include "timer.h"

// #define TEXTO 
#define TO_CSV

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
   
   WriteMatrixToBinary(C, argv[3]);

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
