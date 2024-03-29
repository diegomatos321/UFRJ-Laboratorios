#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include <locale.h>
#include<pthread.h>

typedef struct {
    int threadIndex;
    int startIndex;
    int endIndex;
} tArgs;

float* vetor;
float soma = 0;

void* TarefaSoma(void* arg) {
    pthread_exit(NULL);
    return;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 2)
    {
        wprintf(L"Argumento para números de threads é obrigatório.");
        return EXIT_FAILURE;
    }

    const int nThreads = atoi(argv[1]);
    if (nThreads < 1)
    {
        wprintf(L"Argumento de números de threads precisar ser pelo menos um.");
        return EXIT_FAILURE;
    }

    int TAM_VETOR;
    scanf("%d\n", &TAM_VETOR);

    vetor = (float*) malloc(sizeof(float) * TAM_VETOR);
    if (vetor == NULL)
    {
        wprintf(L"Erro ao alocar memória para o vetor.");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < TAM_VETOR; i++)
        scanf("%f ", &vetor[i]);
    
    pthread_t tid = malloc(sizeof(pthread_t) * nThreads);
    if (tid == NULL)
    {
        wprintf("Erro ao alocar memória para o vetor de identificadores das threads.");
        return EXIT_FAILURE;
    }

    const int TAM_BLOCO = TAM_VETOR / nThreads;
    for (int i = 0; i < TAM_BLOCO; i++)
    {
        tArgs* args = (tArgs*) malloc(sizeof(tArgs));
        if (args == NULL)
        {
            wprintf("--ERRO: malloc() para thread %d", i);
            return;
        }
        
        args->threadIndex = i;
        args->startIndex = i * TAM_BLOCO;
        args-> endIndex = (i + 1) * TAM_BLOCO;

        const int createdCode = pthread_create(tid + i, NULL, TarefaSoma, (void*) args);
        if (createdCode != 0)
        {
            wprintf("--ERRO: pthread_create() no indice: %d", i);
            return;
        }
    }
    
    return EXIT_SUCCESS;
}