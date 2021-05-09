/* Exercicio 1009 */

#include <stdio.h>

int main()
{
  char nomeVendedor[50];
  double salarioFixo, totalVendasMensal, salarioTotal;
  const double comissao = 0.15;

  scanf("%s", &nomeVendedor);
  scanf("%lf", &salarioFixo);
  scanf("%lf", &totalVendasMensal);

  salarioTotal = salarioFixo + (comissao * totalVendasMensal);

  printf("TOTAL = R$ %.2lf\n", salarioTotal);

  return 0;
}