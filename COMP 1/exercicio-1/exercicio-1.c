/* 
    1. Escreva a representação de um algoritmo de cálculo da média de dois
    números quaisquer.
    
    2. Escreva a representação de um algoritmo que calcule as raizes x1 e x2 de
    uma equação de segundo grau.
    
    3. Escreva a representação de um algoritmo que dada a idade de um
    espectador, informe se ele tem permissão para meia-entrada por ser idoso ou não.
    Considere que a pessoa é idosa se tiver mais de 60 anos. 

    Repositório: https://github.com/diegomatos321/Linguagem-C-Pratica
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

const int eACENTUADO = 130, uACENTUADO = 163, iACENTUADO = 161, CEDILHA = 135, aCOMTIL = 198, GRAU = 167;

void resolverPrimeiraTarefa(void);
float calcularMedia(float divisor, float dividendo);

void resolverSegundaTarefa(void);
double * formulaDeBhaskara(double a, double b, double delta);

void resolverTerceiraTarefa(void);
bool forIdoso(int idade);

void tratarMensagemDeError(char text[]);
void definirCorDeTextoParaVermelho(void);
void definirCorDeTextoParaPadrao(void);
bool coeficienteAForInvalido(double a);
bool deltaForInvalido(double delta);

int main(void)
{
    resolverPrimeiraTarefa();
    resolverSegundaTarefa();
    resolverTerceiraTarefa();
    printf("\nPrograma conclu%cdo !", iACENTUADO);
    return 0;
}

void resolverPrimeiraTarefa(void)
{
    float primeiroNumero, segundoNumero, media;
    char escolha;
    bool tarefaResolvida = false;

    while (!tarefaResolvida)
    {
        system("cls");

        printf("=== Primeiro Algoritmo | Calcular a m%cdia entre dois n%cmeros === \n", eACENTUADO, uACENTUADO);
        printf("Digite o primeiro n%cmero: ", uACENTUADO);
        scanf("%f", &primeiroNumero);

        printf("Digite o segundo n%cmero: ", uACENTUADO);
        scanf("%f", &segundoNumero);

        media = calcularMedia(primeiroNumero, segundoNumero);

        system("cls");
        printf("A m%cdia entre %.2f e %.2f %c: %.2f \n", eACENTUADO, primeiroNumero, segundoNumero, eACENTUADO, media);
        printf("Refazer tarefa ? (N/s) \n");
        scanf(" %c", &escolha);

        if (escolha == 'N' || escolha == 'n')
        {
            tarefaResolvida = true;
        }
    }
}

void resolverSegundaTarefa(void)
{
    double a, b, c, delta;
    double *raizes;
    char op;
    bool tarefaResolvida = false;

    while (!tarefaResolvida)
    {
        system("cls");
        printf("=== Segundo Algoritmo | Encontrar as ra%czes de uma equa%c%co do 2%c grau dentro dos conjuntos dos n%cmeros REAIS === \n", iACENTUADO, CEDILHA, aCOMTIL, GRAU, uACENTUADO);
        printf("Digite uma equa%c%co no seguinte formato: \n ax^2 + bx + c \n", CEDILHA, aCOMTIL);
        scanf("%lfx^2 + %lfx + %lf", &a, &b, &c);

        if (coeficienteAForInvalido(a))
        {
            tratarMensagemDeError("O coeficiente 'a' precisa ser diferente de ZERO !");
            continue;
        }

        printf("A equa%c%co desejada %c: %+.2lfx^2 %+.2lfx %+.2lf ? (S/n) \n", CEDILHA, aCOMTIL, eACENTUADO, a, b, c);
        scanf(" %c", &op);

        if (op == 'n' || op == 'N')
        {
            continue;
        }

        delta = pow(b, 2) - (double)4 * a * c;
        if (deltaForInvalido(delta))
        {
            tratarMensagemDeError("Delta e menor que ZERO e nao possui raizes REAIS !");
            continue;
        }

        raizes = formulaDeBhaskara(a, b, delta);
        system("cls");
        printf("As ra%czes da equa%c%co %+.2lfx^2 %+.2lfx %+.2lf %c: \n", iACENTUADO, CEDILHA, aCOMTIL, a, b, c, eACENTUADO);

        printf("x1: %3.2lf \n", raizes[0]);
        printf("x2: %3.2lf \n", raizes[1]);

        free(raizes);

        printf("Desejar refazer a tarefa ? (S/n)");
        scanf(" %c", &op);

        if (op == 'N' || op == 'n')
        {
            tarefaResolvida = true;
        }
    }
}

double *formulaDeBhaskara(double a, double b, double delta)
{
    /* double *raizes = malloc(2 * sizeof(double)); */
    double *raizes = calloc(2, sizeof(double));

    if (!raizes)
    {
        tratarMensagemDeError("Nao foi possivel alocar memoria");
        return NULL;
    }

    raizes[0] = (-b + sqrt(delta)) / (double)2 * a;
    raizes[1] = (-b - sqrt(delta)) / (double)2 * a;

    return raizes;
}

void resolverTerceiraTarefa(void)
{
    int idade;
    bool tarefaResolvida = false;

    while (!tarefaResolvida)
    {
        system("cls");
        printf("=== Terceiro Algoritmo | Permiss%co para meia-entrada por ser idoso ou n%co \n", aCOMTIL, aCOMTIL);
        printf("Digite a idade do espectador: ");
        scanf("%i", &idade);

        /* system("cls"); */

        if (forIdoso(idade))
        {
            printf("Por favor, pague meia-entrada");
            tarefaResolvida = true;
            return;
        }

        printf("Por favor, pague a entrada inteira \nPressione ENTER para continuar");
        getchar();
        getchar();
    }
}

bool forIdoso(int idade)
{
    const int MIN_IDOSO = 60;
    return idade > MIN_IDOSO;
}

bool coeficienteAForInvalido(double a)
{
    return a == 0;
}

bool deltaForInvalido(double delta)
{
    return delta < 0;
}

void tratarMensagemDeError(char text[])
{
    definirCorDeTextoParaVermelho();
    puts(text);
    printf("Pressione ENTER para continuar \n");
    getchar();
    getchar();
    definirCorDeTextoParaPadrao();
}

void definirCorDeTextoParaVermelho(void)
{
    printf("\033[0;31m");
}

void definirCorDeTextoParaPadrao(void)
{
    printf("\033[0m");
}

float calcularMedia(float primeiroNumero, float segundoNumero)
{
    float media = (primeiroNumero + segundoNumero) / 2;

    return media;
}
