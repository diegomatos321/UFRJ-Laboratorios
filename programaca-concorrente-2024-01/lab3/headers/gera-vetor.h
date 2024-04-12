#pragma once

void ReadArguments(char* argv[], int* nLinhas, int* nColunas);
void GenerateRandMatrix(const int TAM_VETOR, float *A);
void WriteToFile(const int nLinhas, const int nColunas, const int TAM_VETOR, float *A, char* fileName);