#include <stdio.h>      // Para funções de entrada/saída como printf, fopen, etc.
#include <stdlib.h>     // Para funções como atoi, exit, etc.
#include <unistd.h>     // Para chamadas de sistema POSIX como fork, sleep, setsid.
#include <signal.h>     // Para manipulação de sinais (signal, SIGTERM, etc).
#include <sys/types.h>  // Para tipos de dados como pid_t.
#include <sys/stat.h>   // Para a função umask.
#include <string.h>     // Para manipulação de strings como strcmp, strstr.
#include <dirent.h>     // Para manipulação de diretórios (opendir, readdir, closedir).
#include <ctype.h>      // Para a função isdigit.
#include <time.h>       // Para obter o timestamp para o log.
#include <errno.h>

int parar = 0;

// função chamada quando o daemon recebe SIGTERM
void handle_sigterm(int sig)
{
    parar = 1;
}

// função para checar se o nome do diretório é numérico (PID)
int eh_numero(const char *str)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return 0;
        }
    }
    return 1;
}

// função para verificar se o processo é zombie
int eh_zombie(const char *pid)
{
    char caminho[256];

    // Monta o caminho para o arquivo "status" do processo[cite: 15].
    snprintf(caminho, sizeof(caminho), "/proc/%s/status", pid);

    FILE *arq = fopen(caminho, "r");
    if (!arq)
        return 0;

    char linha[256];
    int resultado = 0;

    // Lê o arquivo status linha por linha.
    while (fgets(linha, sizeof(linha), arq))
    {
        // Procura pela linha que informa o estado.
        if (strncmp(linha, "State:", 6) == 0)
        {
            // strstr verifica se a substring "zombie" existe na linha.
            if (strchr(linha, 'Z'))
            {
                resultado = 1;
            }
            break;
        }
    }

    fclose(arq);
    return resultado;
}

// função que escreve no log os processos zombies
void checa_zombies(FILE *logf)
{
    DIR *dir = opendir("/proc");
    if (!dir)
    {
        fprintf(logf, "Erro ao abrir /proc: %s\n", strerror(errno));
        return;
    }

    struct dirent *ent;
    int achou = 0;

    time_t agora = time(NULL);
    fprintf(logf, "\n--- Verificação em %s", ctime(&agora));
    fprintf(logf, "PID\tPPID\tNome\n");

    while ((ent = readdir(dir)) != NULL)
    {
        if (!eh_numero(ent->d_name))
            continue;

        if (eh_zombie(ent->d_name))
        {
            char status_path[256];
            snprintf(status_path, sizeof(status_path), "/proc/%s/status", ent->d_name);
            FILE *f = fopen(status_path, "r");
            if (!f)
                continue;

            char linha[256];
            char nome[64] = "(desconhecido)";
            int ppid = -1;

            while (fgets(linha, sizeof(linha), f))
            {
                if (strncmp(linha, "Name:", 5) == 0)
                {
                    sscanf(linha + 5, "%s", nome);
                }
                else if (strncmp(linha, "PPid:", 5) == 0)
                {
                    sscanf(linha + 5, "%d", &ppid);
                }
            }

            fclose(f);
            fprintf(logf, "%s\t%d\t%s\n", ent->d_name, ppid, nome);
            achou = 1;
        }
    }

    if (!achou)
    {
        fprintf(logf, "Nenhum processo ZOMBIE encontrado.\n");
    }

    closedir(dir);
    fflush(logf); // Garante que a mensagem seja escrita imediatamente no disco.
}

int main(int argc, char *argv[])
{
    int intervalo = 3; // padrão de 3 segundos

    if (argc == 2)
    {
        intervalo = atoi(argv[1]);
        if (intervalo <= 0)
            intervalo = 3;
    }

    // instala o tratador de sinal para parar o daemon
    signal(SIGTERM, handle_sigterm);

    // abrir arquivo de log
    FILE *logf = fopen("/tmp/przombies.log", "a");

    if (!logf)
    {
        exit(EXIT_FAILURE);
    }

    fprintf(logf, "Daemon przombies iniciado! Intervalo: %d segundos\n", intervalo);
    fflush(logf);

    // laço principal
    while (!parar)
    {
        checa_zombies(logf);
        sleep(intervalo);
    }

    fprintf(logf, "Daemon przombies finalizado!\n");
    fclose(logf);

    return 0;
}
