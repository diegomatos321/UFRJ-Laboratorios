/* Exercicio 1042 */

#include <stdio.h>

#define TAMANHO_LISTA 8

struct ICodigoDDD
{
  unsigned int DDD;
  char destino[50];
};

int main()
{
  struct ICodigoDDD listaDeDDD[TAMANHO_LISTA] = {
      {61, "Brasilia"},
      {71, "Salvador"},
      {11, "Sao Paulo"},
      {21, "Rio de Janeiro"},
      {32, "Juiz de Fora"},
      {19, "Campinas"},
      {27, "Vitoria"},
      {31, "Belo Horizonte"}};
  int codigoDDD, achou = -1;
  unsigned int i;

  scanf("%i", &codigoDDD);

  for (i = 0; i < TAMANHO_LISTA; i++)
  {
    const struct ICodigoDDD CODIGO = listaDeDDD[i];

    if (codigoDDD == CODIGO.DDD)
    {
      printf("%s\n", CODIGO.destino);
      achou = 1;
      break;
    }
  }

  if (achou == -1)
  {
    printf("DDD nao cadastrado\n");
  }

  return 0;
}