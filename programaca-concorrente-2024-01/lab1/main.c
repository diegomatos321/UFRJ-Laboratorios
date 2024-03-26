#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include <pthread.h>

#define M_THREADS 10
#define TAM_VETOR 100

typedef struct {
    int threadIndex;
    int start;
    int end;
} t_Args;

// Variáveis compartilhadas entre as threads
int vetor[TAM_VETOR], resultados[TAM_VETOR];

void InitializeVector(void) {
    srand(time(NULL));
    for (int i = 0; i < TAM_VETOR; i++)
    {
        vetor[i] = rand();
        resultados[i] = 0;
    }
}

void AssertResults(void) {
    printf("Resultados:\n");
    for (int i = 0; i < TAM_VETOR; i++)
    {
        printf("%d = %d^2\n", resultados[i], vetor[i]);
        assert(resultados[i] == vetor[i] * vetor[i]);
    }
}

void* Quadrado(void* arg) {
    t_Args* args = (t_Args*) arg;

    printf("Executando thread %d\n", args->threadIndex);
    for (int i = args->start; i < args->end; i++)
    {
        resultados[i] = vetor[i] * vetor[i];
    }

    free(args);
    pthread_exit(NULL);
    return NULL;
}

int main(void) {
    InitializeVector();

    pthread_t tid[M_THREADS];

    for (int i = 0; i < M_THREADS; i++)
    {
        // Distribui igualmente o vetor entre as N threads
        t_Args* args;
        args = malloc(sizeof(t_Args));

        if (args == NULL) {
            printf("--ERRO: malloc()\n"); 
            exit(EXIT_FAILURE);
        }

        args->threadIndex = i;
        args->start = i * TAM_VETOR / M_THREADS;
        args->end = (i + 1) * TAM_VETOR / M_THREADS;

        printf("--Cria a thread %d\n", i);
        int code = pthread_create(&tid[i], NULL, Quadrado, (void*) args);
        if (code != 0)
        {
            printf("--ERRO: pthread_create()\n"); 
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < M_THREADS; i++)
    {
        int code = pthread_join(tid[i], NULL);
        if (code != 0)
        {
            printf("--ERRO: pthread_join()\n"); 
            exit(EXIT_FAILURE);
        }
    }

    AssertResults();

    printf("--Thread principal terminou\n");
    pthread_exit(NULL);    
    return EXIT_SUCCESS;
}
