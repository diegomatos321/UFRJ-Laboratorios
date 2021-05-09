/* Exercicio 1005 */

#include <stdio.h>

int main()
{
  const double pesoA = 3.5, pesoB = 7.5;
  double a, b, media;

  scanf("%lf", &a);
  scanf("%lf", &b);

  media = ((a * pesoA) + (b * pesoB))/(pesoA + pesoB);

  printf("MEDIA = %.5lf\n", media);

  return 0;
}