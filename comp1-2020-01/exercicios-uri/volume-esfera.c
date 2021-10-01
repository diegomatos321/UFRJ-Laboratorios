/* Exercicio 1009 */

#include <stdio.h>
#include <math.h>

int main()
{
  double volume, raio;
  const double PI = 3.14159;

  scanf("%lf", &raio);

  volume = (4.0/3.0) * PI * pow(raio, 3.0);

  printf("VOLUME = %.3lf\n", volume);

  return 0;
}