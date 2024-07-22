#include <Matriz.h>

Matriz *CreateMatrix(int rows, int cols)
{
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

void FreeMatrix(Matriz *matrix)
{
   free(matrix->elements);
   free(matrix);
}

Matriz *ReadMatrix(const char *fileName)
{
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

void WriteMatrixToBinary(Matriz *matrix, char *fileName)
{
   FILE *arquivoSaida = fopen(fileName, "wb");
   if (arquivoSaida == NULL)
   {
      wprintf(L"Erro de abertura do arquivo de saída.\n");
      exit(EXIT_FAILURE);
   }

   fwrite(&matrix->rows, sizeof(int), 1, arquivoSaida);
   fwrite(&matrix->cols, sizeof(int), 1, arquivoSaida);
   fwrite(matrix->elements, sizeof(float), matrix->rows * matrix->cols, arquivoSaida);

   fclose(arquivoSaida);
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
