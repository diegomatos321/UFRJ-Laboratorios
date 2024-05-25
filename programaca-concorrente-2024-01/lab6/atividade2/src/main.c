#include "main.h"

int* buffer;
unsigned int BUFFER_SIZE = 0, quantidadePrimos = 0, INPUT_SIZE = 0;
FILE* input_file;
sem_t slotVazio, slotCheio, mutexProdutor, mutexConsumidor;

int main(int argc, char* argv[]) {
    if (argc < 4)
    {
        printf("Usage: ./consumidor-produtor <n_consumidoras> <tamanho_buffer> <input_filename>\n");
        return EXIT_SUCCESS;
    }
    
    // Ler argumentos de entrada
    unsigned int CONSUMIDORES = atoi(argv[1]);
    BUFFER_SIZE = atoi(argv[2]);
    char* input_filename = argv[3];

    // Alocar buffer
    buffer = (int*) malloc(BUFFER_SIZE * sizeof(int));
    if (buffer == NULL)
    {
        printf("ERRO: Ao alocar memória para o buffer\n");
        return EXIT_FAILURE;
    }
    
    // Inicia thread e semaforos
    pthread_t* tid = (pthread_t*) malloc(sizeof(pthread_t) * (CONSUMIDORES + 1)); // +1 para a thread produtora
    sem_init(&slotVazio, 0, BUFFER_SIZE); // Existem BUFFER_SIZE slots vazios
    sem_init(&slotCheio, 0, 0); // Inicialmente não há slots cheios
    sem_init(&mutexProdutor, 0, 1); // binário para exclusão mútua
    sem_init(&mutexConsumidor, 0, 1); // binário para exclusão mútua
    
    // Ler o tamanho da lista de números aleátorios de entrada
    input_file = fopen(input_filename, "rb");
    if (input_file == NULL)
    {
        printf("ERRO: Ao abrir arquivo de entrada\n");
        return EXIT_FAILURE;
    }
    
    fread(&INPUT_SIZE, sizeof(unsigned int), 1, input_file);
    printf("Tamanho do arquivo de entrada: %d\n", INPUT_SIZE);

    // Disparar thread produtora que irá ler inteiro por inteiro
    // do arquivo de entrada e colocar no buffer
    int created = pthread_create(&tid[0], NULL, produtor, NULL);
    if (created != 0)
    {
        printf("ERRO: Ao criar thread produtora\n");
        return EXIT_FAILURE;
    }
    
    // Disparar as threads consumidoras
    for (size_t i = 1; i <= CONSUMIDORES; i++)
    {
        int created = pthread_create(&tid[i], NULL, consumidor, NULL);
        if (created != 0)
        {
            printf("ERRO: Ao criar thread consumidora\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < CONSUMIDORES + 1; i++)
    {
        int status = pthread_join(tid[i], NULL);
        if (status != 0)
        {
            printf("ERRO: pthread_join() retornou %d\n", status);
        }
    }
    printf("Threads terminaram.\n");

    printf("Quantidade de primos: %d\n", quantidadePrimos);

    // Liberar memória alocada
    sem_destroy(&slotVazio);
    sem_destroy(&slotCheio);
    sem_destroy(&mutexConsumidor);
    sem_destroy(&mutexProdutor);

    fclose(input_file);
    free(input_filename);
    free(buffer);

    return EXIT_SUCCESS;
}

void* produtor(void* arg) {
    static unsigned int current_i = 0;
    while (current_i < INPUT_SIZE)
    {
        sem_wait(&slotVazio);
        sem_wait(&mutexProdutor);

        int data = 0;
        size_t items_read = fread(&data, sizeof(int), 1, input_file);
        if (items_read != 1)
        {
            printf("ERRO: fread retornou valor diferente de 1\n");
            sem_post(&mutexProdutor);
            sem_post(&slotVazio);
            break;
        }

        // printf("Produtor leu %d\n", data);
        buffer[current_i % BUFFER_SIZE] = data;
        current_i++;

        sem_post(&mutexProdutor);
        sem_post(&slotCheio);
    }

    printf("Produtor terminou\n");
    free(arg);
    pthread_exit(NULL);
    return NULL;
}

void* consumidor(void* arg) {
    static unsigned int current_i = 0;

    while (current_i < INPUT_SIZE)
    {
        sem_wait(&slotCheio);
        sem_wait(&mutexConsumidor);

        if (current_i == INPUT_SIZE)
        {
            sem_post(&mutexConsumidor);
            sem_post(&slotCheio);
            break;
        }
        
        int data = buffer[current_i % BUFFER_SIZE];
        // printf("Consumidor leu %d\n", data);
        int isPrimo = ehPrimo(data);
        if (isPrimo)
        {
            quantidadePrimos++;
        }
        
        current_i++;

        if (current_i == INPUT_SIZE)
        {
            sem_post(&slotCheio);
        }

        sem_post(&mutexConsumidor);
        sem_post(&slotVazio);
    }
    
    
    printf("Consumidor terminou\n");
    free(arg);
    pthread_exit(NULL);
    return NULL;
}