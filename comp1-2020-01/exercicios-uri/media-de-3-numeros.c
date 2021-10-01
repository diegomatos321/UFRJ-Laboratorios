/* Exercicio 1006 */

#include <stdio.h>

int main()
{
  const double pesoA = 2, pesoB = 3, pesoC = 5;
  double a, b, c, media;

  scanf("%lf", &a);
  scanf("%lf", &b);
  scanf("%lf", &c);

  media = ((a * pesoA) + (b * pesoB) + (c * pesoC))/(pesoA + pesoB + pesoC);

  printf("MEDIA = %.1lf\n", media);

  return 0;
}