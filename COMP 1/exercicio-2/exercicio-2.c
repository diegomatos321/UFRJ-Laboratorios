/* 
  1. Fazer um programa que imprima a média aritmética dos números 7, 8 e 9 e a
  média dos números 4, 5 e 6. Depois este mesmo programa deve calcular a
  soma das duas médias e a médias dessas médias calculadas, mostrando o
  resultado para o usuário.

  2. Criar um programa que calcule o juros pelo atraso de um pagamento,
  recebendo o valor de juros que é cobrado por mês de atraso, a quantidade de
  meses de atraso e o valor original do valor a ser pago.

  3. Leia um número. Se ele for positivo, imprimir a raiz quadrada, senão exibir
  uma mensagem de que não é possível calcular a raiz.

  4. Crie um algoritmo que receba 3 números e informe qual o maior entre eles.
  
  5. Faça um algoritmo que leia dois números e indique se são iguais ou se são
  diferentes. Mostre o maior e o menor (nesta sequência).

  Repositório: https://github.com/diegomatos321/Linguagem-C-Pratica
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

const int eACENTUADO = 130, uACENTUADO = 163, iACENTUADO = 161, CEDILHA = 135, aCOMTIL = 198, GRAU = 167, eCIRCUNFLEXO = 136, aACENTUADO = 160;

void realizarPrimeiraTarefa(void);
int calcularMediaEntreNumeros(int lista[]);

void realizarSegundaTarefa(void);
bool calcularJurosSimples(void);
bool calcularJurosCompostos(void);

void realizarTerceiraTarefa(void);

void realizarQuartaTarefa(void);
double encontrarMaiorNumero(double listaDeNumeros[3]);

void realizarQuintaTarefa(void);

bool desejaRefazerCalculo(void);
void tratarMensagemDeError(char text[]);
void definirCorDeTextoParaVermelho(void);
void definirCorDeTextoParaPadrao(void);

int main(void)
{
  realizarPrimeiraTarefa();
  realizarSegundaTarefa();
  realizarTerceiraTarefa();
  realizarQuartaTarefa();
  realizarQuintaTarefa();
  return 0;
}

void realizarPrimeiraTarefa(void)
{
  int primeiraLista[3] = {7, 8, 9};
  int segundaLista[3] = {4, 5, 6};
  int primeiraMedia, segundaMedia, somaDasMedias;

  system("cls");
  printf("=== Primeiro Algoritmo | Calcular m%cdia entre n%cmeros === \n", eACENTUADO, uACENTUADO);

  primeiraMedia = calcularMediaEntreNumeros(primeiraLista);
  printf("M%cdia entre os primeiros n%cmeros: %i \n", eACENTUADO, uACENTUADO, primeiraMedia);

  segundaMedia = calcularMediaEntreNumeros(segundaLista);
  printf("M%cdia entre os segundos n%cmeros: %i \n", eACENTUADO, uACENTUADO, segundaMedia);

  somaDasMedias = primeiraMedia + segundaMedia;
  printf("A soma das m%cdias %c: %i \n", eACENTUADO, eACENTUADO, somaDasMedias);

  printf("Aperte ENTER para continuar \n");
  getchar();
}

int calcularMediaEntreNumeros(int lista[])
{
  /* int quantidadeDeElementos = sizeof(lista) / sizeof(lista[0]); */
  int quantidadeDeElementos = 3;
  int media, somaDosElementos = 0, i;

  for (i = 0; i < quantidadeDeElementos; i++)
  {
    somaDosElementos += lista[i];
  }

  media = somaDosElementos / quantidadeDeElementos;
  return media;
}

void realizarSegundaTarefa(void)
{
  bool exercicioResolvido = false;
  char op;

  while (!exercicioResolvido)
  {
    system("cls");
    printf("=== Segundo Algoritmo | Calcular Juros === \n");
    printf("Escolha entre: \n");
    printf("[1] - Juros Simples \n");
    printf("[2] - Juros Compostos \n");
    scanf(" %c", &op);

    if (op == '1')
    {
      exercicioResolvido = calcularJurosSimples();
    }
    else if (op == '2')
    {
      exercicioResolvido = calcularJurosCompostos();
    }
    else
    {
      tratarMensagemDeError("Por favor, selecione uma das duas opcoes: 1 ou 2");
      continue;
    }
  }
}

bool calcularJurosSimples(void)
{
  double capital, juros, taxaDeJuros, periodoDeCapitalizacao;

  system("cls");
  printf("=== Vamos calcular os Juros Simples de uma d%cvida === \n", iACENTUADO);

  printf("Qual %c a taxa de Juros ? \n", eACENTUADO);
  scanf("%lf", &taxaDeJuros);

  printf("Quanto de Capital inicial ? \n");
  scanf("%lf", &capital);

  printf("Ha quanto tempo esta sem pagar sua d%cvida ? \n", iACENTUADO);
  scanf("%lf", &periodoDeCapitalizacao);

  juros = capital * taxaDeJuros * periodoDeCapitalizacao;

  printf("Voc%c possui R$ %.2lf de Juros acumulados ;( \n", eCIRCUNFLEXO, juros);

  return desejaRefazerCalculo();
}

bool calcularJurosCompostos(void)
{
  double capital, juros, taxaDeJuros, periodoDeCapitalizacao, montante;

  system("cls");
  printf("=== Vamos calcular os Juros Compostos de uma d%cvida === \n", iACENTUADO);

  printf("Qual %c a taxa de Juros ? \n", eACENTUADO);
  scanf("%lf", &taxaDeJuros);

  printf("Quanto de Capital inicial ? \n");
  scanf("%lf", &capital);

  printf("Ha quanto tempo esta sem pagar sua d%cvida ? \n", iACENTUADO);
  scanf("%lf", &periodoDeCapitalizacao);

  montante = capital * (pow((1 + taxaDeJuros), periodoDeCapitalizacao));
  juros = montante - capital;

  printf("Voc%c possui R$ %.2lf de Juros acumulados ;( \n", eCIRCUNFLEXO, juros);

  return desejaRefazerCalculo();
}

void realizarTerceiraTarefa(void)
{
  bool exercicioResolvido = false;
  double numero, raizQuadrada;

  while (!exercicioResolvido)
  {
    system("cls");
    printf("=== Terceiro Algoritmo | Calcular raiz quadrada de n%cmeros reais === \n", uACENTUADO);
    printf("Digite um n%cmero: ", uACENTUADO);
    scanf("%lf", &numero);

    if (numero < 0)
    {
      tratarMensagemDeError("Digite um numero positivo !");
      continue;
    }

    raizQuadrada = sqrt(numero);

    printf("A raiz quadrada de %.2lf %c %.2lf \n", numero, eACENTUADO, raizQuadrada);

    exercicioResolvido = desejaRefazerCalculo();
  }
}

void realizarQuartaTarefa(void)
{
  bool exercicioResolvido = false;
  double listaDeNumeros[3], maiorNumero;
  int i;

  while (!exercicioResolvido)
  {
    system("cls");
    printf("=== Quarto Algoritmo | Vamos encontrar o maior n%cmero entre 3 n%cmeros === \n", uACENTUADO, uACENTUADO);

    for (i = 0; i < 3; i++)
    {
      printf("Digite o %i%c n%cmero: ", i, GRAU, uACENTUADO);
      scanf("%lf", &listaDeNumeros[i]);
    }

    maiorNumero = encontrarMaiorNumero(listaDeNumeros);

    printf("O maior n%cmero %c: %.2lf \n", uACENTUADO, eACENTUADO, maiorNumero);

    exercicioResolvido = desejaRefazerCalculo();
  }
}

void realizarQuintaTarefa(void)
{
  bool exercicioResolvido = false;
  double primeiroNumero, segundoNumero;

  while (!exercicioResolvido)
  {
    system("cls");
    printf("=== Quinta Algoritmo | Numeros Iguais ou diferentes === \n", uACENTUADO, uACENTUADO);

    printf("Digite o primeiro n%cmero: ", uACENTUADO);
    scanf("%lf", &primeiroNumero);

    printf("Digite o segundo n%cmero: ", uACENTUADO);
    scanf("%lf", &segundoNumero);

    if (primeiroNumero == segundoNumero)
    {
      printf("Os n%cmeros %.2lf e %.2lf s%co iguais ! \n", uACENTUADO, primeiroNumero, segundoNumero, aCOMTIL);
    }
    else
    {
      printf("Os n%cmeros %.2lf e %.2lf s%co diferentes ! \n", uACENTUADO, primeiroNumero, segundoNumero, aCOMTIL);
    }

    exercicioResolvido = desejaRefazerCalculo();
  }
}

double encontrarMaiorNumero(double listaDeNumeros[3])
{
  double candidatoAMaiorNumero = -1;
  int i;

  for (i = 0; i < 3; i++)
  {
    const double elemento = listaDeNumeros[i];

      if (elemento > candidatoAMaiorNumero)
      {
        candidatoAMaiorNumero = elemento;
        continue;
      }
  }

  return candidatoAMaiorNumero;
}

bool desejaRefazerCalculo(void)
{
  char op;

  printf("Deseja refazer o c%clculo ? (S/n)", aACENTUADO);
  scanf(" %c", &op);

  if (op == 'n' || op == 'N')
  {
    return true;
  }

  return false;
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
