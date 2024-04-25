#include "main.h"

long long int N = 0, i_global = 0;
pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    double start, end, delta;

    if (argc < 3)
    {
        wprintf(L"Quantidade N de números e nThreads são obrigatórios.\n");
        return EXIT_FAILURE;
    }

    N = atoll(argv[1]);
    if (N <= 0)
    {
        wprintf(L"O número deve ser positivo.\n");
        return EXIT_FAILURE;
    }

    pthread_mutex_init(&mutex, NULL);

    GET_TIME(start);

    int nThreads = atoi(argv[2]);
    pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * nThreads);
    for (int i = 0; i < nThreads; i++)
    {
        int creationStatusCode = pthread_create(tid + i, NULL, contaPrimo, NULL);

        if (creationStatusCode != 0)
        {
            wprintf(L"ERRO: Criaçao da Thread %d falhou.", i);
        }
    }

    long long int total = 0;
    for (int i = 0; i < nThreads; i++)
    {
        long long int *retorno;
        int joinStatusCode = pthread_join(tid[i], (void*)&retorno);
        wprintf(L"Thread %d retornou %lld\n", i, *retorno);

        if (joinStatusCode != 0)
        {
            wprintf(L"ERRO: pthread_join falhou para Thread %d.", i);
        }

        total += *retorno;
        free(retorno);
    }

    GET_TIME(end);   
    delta = end - start;
    wprintf(L"Tempo para contar os primos: %lf\n", delta);
    
    wprintf(L"Total de primos: %lld\n", total);

    pthread_mutex_destroy(&mutex);
    free(tid);

    return 0;
}

void* contaPrimo(void* arg)
{
    pthread_mutex_lock(&mutex);
    long long int i_local = i_global;
    i_global++;
    pthread_mutex_unlock(&mutex);

    long long int *total = malloc(sizeof(long long int));
    *total = 0;

    while(i_local < N)
    {
        if (ehPrimo(i_local))
            *total += 1;
        
        pthread_mutex_lock(&mutex);
        i_local = i_global;
        i_global++;
        pthread_mutex_unlock(&mutex);
    }

    free(arg);
    pthread_exit((void*) total);
    return NULL;
}

int ehPrimo(long long int n)
{
    long long int i;
    if (n <= 1)
        return 0;
    if (n == 2)
        return 1;
    if (n % 2 == 0)
        return 0;
    for (i = 3; i < sqrt(n) + 1; i += 2)
        if (n % i == 0)
            return 0;
    return 1;
}