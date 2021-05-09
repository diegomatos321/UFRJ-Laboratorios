/* Exercicio 1042 */

#include <stdio.h>
#include <stdlib.h>

void quicksort(int listaDeNumeros[3], int inicio, int fim);
void copyArray(int source[3], int destiny[3]);
void ordernarNumeros(int listaDeNumeros[3], int inicio, int fim);

int main()
{
  int numeros[3], originais[3];
  unsigned int i;

  scanf("%i %i %i", &numeros[0], &numeros[1], &numeros[2]);
  /*   scanf("%i", &numeros[0]);
  scanf("%i", &numeros[1]);
  scanf("%i", &numeros[2]); */

  copyArray(numeros, originais);
  quicksort(numeros, 0, 3);

  for (i = 0; i < 3; i++)
  {
    printf("%i\n", numeros[i]);
  }

  printf("\n");

  for (i = 0; i < 3; i++)
  {
    printf("%i\n", originais[i]);
  }

  return 0;
}

void copyArray(int source[3], int destiny[3])
{
  int unsigned i;

  for (i = 0; i < 3; i++)
  {
    destiny[i] = source[i];
    /* printf("%i - Origem: %i, Destino: %i\n", i, source[i], destiny[i]); */
  }
}

void quicksort(int listaDeNumeros[3], int inicio, int fim)
{
  int i, j, pivo, aux;

  i = inicio;
  j = fim;
  pivo = listaDeNumeros[(inicio + fim) / 2];

  while (i <= j)
  {
    while (listaDeNumeros[i] < pivo && i < fim)
    {
      i++;
    }

    while (listaDeNumeros[j] > pivo && j > inicio)
    {
      j--;
    }

    if (i <= j)
    {
      aux = listaDeNumeros[i];
      listaDeNumeros[i] = listaDeNumeros[j];
      listaDeNumeros[j] = aux;
      i++;
      j--;
    }
  }

  if (j > inicio)
  {
    quicksort(listaDeNumeros, inicio, j);
  }

  if (i < fim)
  {
    quicksort(listaDeNumeros, i, fim);
  }
}
