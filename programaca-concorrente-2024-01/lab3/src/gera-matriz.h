#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include <locale.h>
#include "commons/Matriz.h"

void ReadArguments(char* argv[], int *rows, int *cols);
Matriz* GenerateRandMatrix(const int cols, const int rows);
