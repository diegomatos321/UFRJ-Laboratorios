/* Exercicio 1008 */

#include <stdio.h>

int main()
{
  int numeroFuncionario, horasTrabalhadas;
  float valorHora, salario;

  scanf("%i", &numeroFuncionario);
  scanf("%i", &horasTrabalhadas);
  scanf("%f", &valorHora);

  salario = horasTrabalhadas * valorHora;

  printf("NUMBER = %i\n", numeroFuncionario);
  printf("SALARY = U$ %.2f\n", salario);

  return 0;
}
