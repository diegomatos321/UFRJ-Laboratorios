/* 
  Nome: Diego Vasconcelos Schardosim de Matos
  DRE: 120098723
*/

#include <stdio.h>
#include <stdlib.h>

#define PLAYING 1
#define GAME_OVER 0

int main()
{
  /* TODO: CALCULAR MINAS AO REDOR */
  int tabuleiro[10][10] = {
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2}
  };
  const int MAX_MINES = 10;
  int GAME_STATE = PLAYING;
  unsigned int linha, coluna, mines = 0;

  /* DEFINIR MINAS */
  while (mines < MAX_MINES)
  {
    for (linha = 0; linha < 10; linha++)
    {
      for (coluna = 0; coluna < 10; coluna++)
      {
        /* Correto ? Não precisa definir a seed ? */
        int random = rand() % 11;
        if (random > 7)
        {
          tabuleiro[linha][coluna] = -1;
          mines++;
        }
      }
    }
  }

  while (GAME_STATE == PLAYING)
  {
    int posX, posY, achou = 0, casa, bombasProximas = 0, i, j;

    /* DESENHAR TABULEIRO */
    for (linha = 0; linha < 10; linha++)
    {
      for (coluna = 0; coluna < 10; coluna++)
      {
        /* Casa Revelada */
        if (tabuleiro[linha][coluna] >= 0)
        {
          printf("[%i] ", tabuleiro[linha][coluna]);
        }
        else
        {
          printf("[%i, %i] ", linha, coluna);
        }

        if (coluna == 9)
        {
          printf("\n");
        }
      }
    }

    printf("=== CAMPO MINADO | ESCOLHA UMA POSICAO ===\n");
    printf("Exemplo: 2 1\n");
    scanf("%i %i", &posY, &posX);

    for (linha = 0; linha < 10 && achou == 0; linha++)
    {
      if (linha == posY)
      {
        for (coluna = 0; coluna < 10; coluna++)
        {
          if (coluna == posX)
          {
            casa = tabuleiro[linha][coluna];
            achou = 1;
            break;
          }
        }
      }
    }

    if (achou == 0)
    {
      printf("Digite uma casa valida !");
    }
    else if (casa == -1)
    {
      printf("BOMBA ! Voce perdeu !\n");
      GAME_STATE = GAME_OVER;
    }
    else
    {
      for (i = -1; i < 2; i++)
      {
        for (j = -1; j < 2; j++)
        {
          if (i == 0 && j == 0)
          {
            continue;
          }
          /* printf("[%i] [%i] == %i \n", i, j, tabuleiro[posY + i][posX + j]); */
          if (tabuleiro[posY + i][posX + j] == -1)
          {
            bombasProximas++;
          }
        }
      }
      
      tabuleiro[posY][posX] = bombasProximas;
    }
  }

  return 0;
}
