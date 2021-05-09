/* Exercicio 1073 */

#include <stdio.h>

#define MINIMO 5
#define MAXIMO 2000

int main()
{
  int numero;
  unsigned int i;

  scanf("%i", &numero);

  if (numero < 5 || numero > 2000)
  {
    return (1);
  }

  for (i = 2; i <= numero; i += 2)
  {
    const int QUADRADO = i * i;

    printf("%i^2 = %i\n", i, QUADRADO);
  }

  return 0;
}