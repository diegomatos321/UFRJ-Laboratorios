Abra o arquivo exemplo1.c e entenda o que ele faz.

1. Os valores impressos foram sempre o valor esperado? Se não, explique por que
isso aconteceu?

Os valores impressão não foram sempre o valor esperado, isso acontece por conta do entrelaçamento da execução das instruções de máquinas, ou seja, a corrida de dados.

2. É possível que a variável soma termine com valor acima de 200000? Por que?

Sim, é possível, basta que a ordem de execução das threads não sobrescreva os valores da variável soma.

Abra o arquivo exemplo2.c e compreenda como locks são usados para implemen tar a exclusãao mútua entre as threads.

3. Execute o programa várias vezes. Os valores impressos foram sempre o valor
esperado? Por que?

Sim, pois agora o programa concorrente possui comunicação e sincronização entre as threads na seção crítica da soma através da exclusão mútua, ou seja, apenas um fluxo de execução a cada vez.


