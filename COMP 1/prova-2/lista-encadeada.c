/* 
  NOME: Diego Vasconcelos Schardosim de Matos
  DRE: 120098723
*/

#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

typedef struct NODE
{
  int DATA;
  struct NODE *NEXT;
} NODE;

void createNewNodeAndInsertIt(int num);
NODE *newNode(int data);

NODE **searchFor(int x);
void removeFirstElement(int x);
void insertBefore(int x, int y);

void printAllNodes(NODE *currentNode);

NODE *head = NULL;

int main()
{
  int finish = FALSE;

  while (!finish)
  {
    int num = 0;

    scanf("%i", &num);

    if (num < 0)
    {
      finish = TRUE;
      continue;
    }

    createNewNodeAndInsertIt(num);
  }

  finish = FALSE;
  while (!finish)
  {
    char op = 'x';
    int x = 0, y = 0;

    scanf(" %c", &op);

    if (op == 'X' || op == 'x')
    {
      finish = TRUE;
      break;
    }
    else
    {
      do
      {

      } while (getchar() != ' ');
    }

    if (op == 'R' || op == 'r')
    {
      scanf("%i", &x);
      removeFirstElement(x);
    }
    else if (op == 'I' || op == 'i')
    {
      scanf("%i %i", &y, &x);
      insertBefore(y, x);
    }
  }

  printAllNodes(head);

  return 0;
}

void createNewNodeAndInsertIt(int data)
{
  NODE *tempNode;
  tempNode = newNode(data);
  tempNode->NEXT = head;
  head = tempNode;
}

NODE *newNode(int data)
{
  NODE *tempNode = (NODE *)malloc(sizeof(NODE));
  tempNode->DATA = data;
  tempNode->NEXT = NULL;

  return tempNode;
}

void removeFirstElement(int x)
{
  NODE **prevAndCurrent;
  NODE *elementNode;
  NODE *prevNode;

  prevAndCurrent = searchFor(x);
  prevNode = prevAndCurrent[0];
  elementNode = prevAndCurrent[1];

  if (prevNode == NULL)
  {
    return;
  }

  if (elementNode == head)
  {
    head = elementNode->NEXT;
  }
  else
  {
    prevNode->NEXT = elementNode->NEXT;
  }

  free(elementNode);
  free(prevAndCurrent);
}

/* A função retorna NULO no primeiro parâmetro caso não encontre a casa desejada */
NODE **searchFor(int x)
{
  int achou = FALSE;
  NODE **prevAndCurrent = (NODE **)malloc(2 * sizeof(NODE));
  NODE *currentNode = head;
  NODE *prevNode;

  while (!achou)
  {
    if (currentNode->DATA == x)
    {
      achou = TRUE;
      break;
    }
    if (currentNode->NEXT == NULL)
    {
      break;
    }

    prevNode = currentNode;
    currentNode = currentNode->NEXT;
  }

  if (achou == FALSE)
  {
    prevAndCurrent[0] = NULL;
  }
  else
  {
    prevAndCurrent[0] = prevNode;
  }

  prevAndCurrent[1] = currentNode;
  return prevAndCurrent;
}

void insertBefore(int y, int x)
{
  NODE **prevAndCurrent;
  NODE *elementNode;
  NODE *prevNode;
  NODE *tempNode = newNode(x);

  prevAndCurrent = searchFor(y);
  prevNode = prevAndCurrent[0];
  elementNode = prevAndCurrent[1];

  if (prevNode == NULL)
  {
    elementNode->NEXT = tempNode;
    return;
  }

  if (elementNode == head)
  {
    head = tempNode;
  }
  else
  {
    prevNode->NEXT = tempNode;
  }

  tempNode->NEXT = elementNode;

  free(prevAndCurrent);
}

void printAllNodes(NODE *currentNode)
{
  printf("%i ", currentNode->DATA);

  if (currentNode->NEXT == NULL)
  {
    printf("\n");
    return;
  }

  printAllNodes(currentNode->NEXT);
}