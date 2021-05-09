/* Exercicio 1019 */

#include <stdio.h>

int main()
{
  int horas, minutos, segundos, tempoTotalEmSegundos;

  scanf("%i", &tempoTotalEmSegundos);

  minutos = tempoTotalEmSegundos / 60;
  horas = minutos / 60;
  segundos = tempoTotalEmSegundos % 60;

  /* Encontrar o menor numero modulo 60 */
  while (minutos - 60 >= 0)
  {
    minutos -= 60;
  }

  printf("%i:%i:%i\n", horas, minutos, segundos);

  return 0;
}
