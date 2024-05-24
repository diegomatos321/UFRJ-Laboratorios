#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CONSUMIDORES 10

void* produtor(void* arg);
void* consumidor(void* arg);

int* buffer;
unsigned int BUFFER_SIZE = 0, INPUT_SIZE = 0;
FILE* input_file;
sem_t slotVazio, mutextProdutor;

int main(int argc, char* argv[]) {
    if (argc < 4)
    {
        printf("Usage: ./consumidor-produtor <input_filename> <tamanho_buffer> <output_filename>\n");
        return EXIT_SUCCESS;
    }
    
    // Ler argumentos de entrada
    const char* input_filename = argv[1];
    BUFFER_SIZE = atoi(argv[2]);
    const char* output_filename = argv[3];

    // Alocar buffer
    buffer = (int*) malloc(BUFFER_SIZE * sizeof(int));

    pthread_t tid[CONSUMIDORES + 1]; // +1 para a thread produtora
    
    // Ler tamanho da lista de numeros aleatorios de entrada
    input_file = fopen(input_filename, "rb");
    fread(&INPUT_SIZE, sizeof(unsigned int), 1, input_file);

    // Disparar thread produtora que irá ler byte a byte os números
    // do arquivo de entrada e colocar no buffer
    int created = pthread_create(&tid[0], NULL, produtor, NULL);
    if (created != 0)
    {
        printf("Erro ao criar thread produtora\n");
        return EXIT_FAILURE;
    }
    
    // Disparar as threads consumidoras
    for (int i = 1; i < CONSUMIDORES; i++)
    {
        int created = pthread_create(&tid[i], NULL, consumidor, NULL);
        if (created != 0)
        {
            printf("Erro ao criar thread consumidora\n");
            return EXIT_FAILURE;
        }
    }

    // Liberar memória alocada
    fclose(input_file);
    free(input_filename);
    free(output_filename);
    free(buffer);
}

void* produtor(void* arg) {
    static int current_i = 0;
    for (current_i = 0; current_i < INPUT_SIZE - 1; current_i++)
    {
        fread(buffer[current_i % BUFFER_SIZE], sizeof(int), 1, input_file);
    }

    free(arg);
    pthread_exit(NULL);
    return NULL;
}

void* consumidor(void* arg) {
    free(arg);
    pthread_exit(NULL);
    return NULL;
}