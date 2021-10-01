#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
/* #define MEMORIA_LIMITE 200 */ /* Simular memoria limitada */

int main() {
  int memoryLeak = FALSE;
  /* int memoriaAlocada = 0, iteracoes = 0; */

  while(!memoryLeak)
  {
    int *carga = (int*) malloc(sizeof(int));
    /* iteracoes++; */

    if (carga == NULL)
    {
      memoryLeak = TRUE;
      continue;
    }

/*     memoriaAlocada = iteracoes * sizeof(int);
    if(memoriaAlocada == MEMORIA_LIMITE)
    {
      printf("Acabou a memoria!\n");
      memoryLeak = TRUE;
      continue;
    } */

    scanf("%i", carga);

    if (*carga == 0)
    {
      break;
    }
  }

  if (!memoryLeak)
  {
    printf("Pronto para decolar!\n");
  }
  else
  {
    printf("Sobrepeso!\n");
  }

  return 0;
}