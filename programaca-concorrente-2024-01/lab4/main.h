#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <locale.h>
#include <wchar.h>
#include "timer.h"

void* contaPrimo(void* arg); // Função que será executada pelas threads
int ehPrimo(long long int n);
