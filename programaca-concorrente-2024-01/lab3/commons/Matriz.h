#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

typedef struct {
   int rows;
   int cols;
   float *elements;
} Matriz;

Matriz* CreateMatrix(int rows, int cols);
void FreeMatrix(Matriz *matrix);
Matriz* ReadMatrix(const char *fileName);
void WriteMatrixToBinary(Matriz *matrix, char *fileName);
void PrintMatrix(Matriz *matrix);
