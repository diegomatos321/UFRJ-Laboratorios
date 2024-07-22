#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "./include/ehprimo.h"
#include "./include/concat.h"

// #define CONSUMIDORES 2

void* produtor(void* arg);
void* consumidor(void* arg);
