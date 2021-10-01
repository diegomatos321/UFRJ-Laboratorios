/* 
  Nome: Diego Vasconcelos Schardosim de Matos
  DRE: 120098723
*/

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAXIMO 1024

int main()
{
  char destino[TAMANHO_MAXIMO], origem[TAMANHO_MAXIMO];
  unsigned int i;
  int tamanho;

  printf("O algoritmo ira copiar a primeira frase para a segunda frase.\n");
  printf("Digite a primeira frase com ate %i caracteres:\n", TAMANHO_MAXIMO);
  fgets(origem, sizeof(origem), stdin);

  printf("Digite a segunda frase com ate %i caracteres:\n", TAMANHO_MAXIMO);
  fgets(destino, sizeof(destino), stdin);

  printf("Quantos caracteres devem ser copiados ?\n");
  scanf("%i", &tamanho);

  /* 
    The C library function char *strncpy(char *dest, const char *src, size_t n) copies up to n characters from the string pointed to, by src to dest. In a case where the length of src is less than that of n, the remainder of dest will be padded with null bytes.
 */
  for (i = 0; i < TAMANHO_MAXIMO; i++)
  {
    if (origem[i] == '\0')
    {
      break;
    }

    if (i < tamanho)
    {
      destino[i] = origem[i];
    }
    else
    {
      destino[i] = ' ';
    }
    /* Não funcionou... */
    /*     
    else
        {
          destino[i] = NULL;
        }
    */
  }

  printf("Frase copiada de: %s\n", origem);
  printf("Para: %s\n", destino);

  return 0;
}