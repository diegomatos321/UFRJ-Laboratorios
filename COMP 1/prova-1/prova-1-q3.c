/* 
  Nome: Diego Vasconcelos Schardosim de Matos
  DRE: 120098723
*/

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAXIMO 258

int main()
{
  char frase[TAMANHO_MAXIMO], busca;
  int i;

  printf("Digite uma frase\n");
  fgets(frase, sizeof(frase), stdin);

  printf("Qual caracter eu devo procurar dentro dessa frase ?\n");
  scanf("%c", &busca);

  /* 
  The C library function char *strchr(const char *str, int c) searches for the first occurrence of the character c (an unsigned char) in the string pointed to by the argument str.
  */
  for (i = 0; i < TAMANHO_MAXIMO; i++)
  {
    if (frase[i] == busca)
    {
      printf("Character encontrado na posicao: %i", i + 1);
      exit(0);
    }

    if (i == TAMANHO_MAXIMO)
    {
      printf("Character nao encontrado");
      exit(1);
    }
  }

  return 0;
}