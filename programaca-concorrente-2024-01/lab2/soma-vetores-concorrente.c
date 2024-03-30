#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include <locale.h>
#include <pthread.h>
#include <math.h>

typedef struct {
    int threadIndex;
    int startIndex;
    int endIndex;
} tArgs;

float* vetor;

void* TarefaSoma(void* arg) {
    tArgs* args = (tArgs*) arg;

    wprintf(L"Executando thread %d\n", args->threadIndex);

    float* result = malloc(sizeof(float));
    for (int i = args->startIndex; i < args->endIndex; i++)
    {
        *result += vetor[i];
    }
    
    // liberar memoria do argumento
    free(args);
    pthread_exit((void*) result);
    return NULL;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 2)
    {
        wprintf(L"Argumento para números de threads é obrigatório.\n");
        return EXIT_FAILURE;
    }

    const int nThreads = atoi(argv[1]);
    if (nThreads < 1)
    {
        wprintf(L"Argumento de números de threads precisar ser pelo menos um.\n");
        return EXIT_FAILURE;
    }

    int TAM_VETOR;
    scanf("%d", &TAM_VETOR);

    vetor = (float*) malloc(sizeof(float) * TAM_VETOR);
    if (vetor == NULL)
    {
        wprintf(L"Erro ao alocar memória para o vetor.\n");
        return EXIT_FAILURE;
    }
    
    wprintf(L"Carregando vetor do arquivo...\n");
    for (int i = 0; i < TAM_VETOR; i++)
        scanf("%f", &vetor[i]);
    wprintf(L"Vetores carregados.\n");
    
    float SOMA_CORRETA;
    scanf("%f", &SOMA_CORRETA);

    pthread_t* tid = malloc(sizeof(pthread_t) * nThreads);
    if (tid == NULL)
    {
        wprintf(L"Erro ao alocar memória para o vetor de identificadores das threads.\n");
        return EXIT_FAILURE;
    }

    const int TAM_BLOCO = TAM_VETOR / nThreads;
    for (int i = 0; i < nThreads; i++)
    {
        tArgs* args = (tArgs*) malloc(sizeof(tArgs));
        if (args == NULL)
        {
            wprintf(L"--ERRO: malloc() para thread %d\n", i);
            return EXIT_FAILURE;
        }
        
        args->threadIndex = i;
        args->startIndex = i * TAM_BLOCO;
        args-> endIndex = (i + 1) * TAM_BLOCO;

        const int createdCode = pthread_create(tid + i, NULL, TarefaSoma, (void*) args);
        if (createdCode != 0)
        {
            wprintf(L"--ERRO: pthread_create() no indice: %d\n", i);
            return EXIT_FAILURE;
        }
    }

    float soma = 0;
    for (int i = 0; i < nThreads; i++)
    {
        float* result;
        const int finishedCode = pthread_join(*(tid + i), (void*) &result);
        if (finishedCode != 0)
        {
            wprintf(L"--ERRO: pthread_join() no indice: %d\n", i);
            continue;
        }

        soma += *result;

        free(result);
    }
    
    wprintf(L"O programa concorrente somou %f\n", soma);
    wprintf(L"O resultado correto da soma é %f\n", SOMA_CORRETA);
    
    static const float MARGIN_ERROR = 10E-1;
    if (fabs(SOMA_CORRETA - soma) < MARGIN_ERROR)
    {
        wprintf(L"O programa concorrente somou os vetores dentro de uma margin de erro tolerável.\n");
    } else {
        wprintf(L"-FALHOU: O programa falhou em somar os vetores.\n");
    }
    
    free(vetor);
    free(tid);
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}