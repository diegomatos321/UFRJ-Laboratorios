/* 
  NOME: Diego Vasconcelos Schardosim de Matos
  DRE: 120098723
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PESSOA
{
  char nome[50];
  char sexo;
  int idade;
  struct PESSOA *p_prox;
} PESSOA;

int insere_pessoa(PESSOA *p_head, PESSOA *p_novo);

int main(void)
{
  PESSOA *p, pessoa1;
  PESSOA *p_head = NULL;

  if ((p = (PESSOA *)malloc(sizeof(PESSOA))) == NULL)
  {
    return 1;
  }

  strcpy(p->nome, "Pessoa1");
  p->sexo = 'F';
  p->idade = 42;
  p->p_prox = NULL;
  p_head = p;

  strcpy(pessoa1.nome, "Pessoa2");
  pessoa1.sexo = 'M';
  pessoa1.idade = 18;
  pessoa1.p_prox = NULL;

  insere_pessoa(p_head, &pessoa1);

  p = p_head;

  while (p != NULL)
  {
    printf("%s %c %d\n", p->nome, p->sexo, p->idade);

    p = p->p_prox;
  }

  return 0;
}

int insere_pessoa(PESSOA *p_head, PESSOA *p_novo)
{
  /* PESSOA *tempPessoa = p_head; */
  
  /* Inserir nova pessoa no final com apenas com duas pessoas */
  p_head -> p_prox = p_novo;

  /*   
    Inserir nova pessoa no inicio
    p_novo -> p_prox = p_head;
    p_head = p_novo; 
  */

  /*   
    Inserir nova pessoa no final com número indeterminado de nós
    while(1)
    {
      if (tempPessoa -> p_prox == NULL)
      {
        tempPessoa -> p_prox = p_novo;
        break;
      }

      tempPessoa = tempPessoa -> p_prox;
    } 
  */

  return 0;
}
