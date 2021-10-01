/* Exercicio 1002 */

#include <stdio.h>

int main()
{
  const double PI = 3.14159;
  double raio, area;

  scanf("%lf", &raio);

  area = PI * raio * raio;

  printf("A=%.4lf\n", area);

  return 0;
}