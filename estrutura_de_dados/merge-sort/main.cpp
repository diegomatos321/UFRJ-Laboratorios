#include <iostream>
#define TAM 10

using namespace std;

void mergeSort(int arr[], int inicio, int fim);
void merge(int arr[], int inicio, int meio, int fim);
void printArray(int arr[], int tam);

class Pilha
{
private:
  int *pilha;
  int index = -1;
  int tamanhoDaPilha;

  void redimensiona(int novoTamanho)
  {
    if (tamanhoDaPilha == novoTamanho)
    {
      return;
    }

    int *novaPilha;

    novaPilha = (int *)realloc(pilha, novoTamanho * sizeof(int));

    if (novaPilha != NULL)
    {
      pilha = novaPilha;

      if (novoTamanho < index + 1)
      {
        index = novoTamanho - 1;
      }

      tamanhoDaPilha = novoTamanho;
    }
    else
    {
      puts("Error (re)allocating memory");
      exit(1);
    }
  }

public:
  Pilha(int novoTamanho = 10)
  {
    pilha = (int *)malloc(novoTamanho * sizeof(int));
    tamanhoDaPilha = novoTamanho;
  }

  void empilha(int numero)
  {
    index++;

    if (index >= tamanhoDaPilha - 1)
    {
      redimensiona(2 * tamanhoDaPilha);
    }

    pilha[index] = numero;
  }

  void print()
  {
    for (int i = 0; i <= index; i++)
    {
      cout << pilha[i] << endl;
    }
  }

  int topo()
  {
    return index;
  }

  int* toArray()
  {
    return pilha;
  }
};

int main()
{
  Pilha pilhaDeInteiros(TAM);
  int input = 0;

  while (!feof(stdin))
  {
    if (scanf("%d", &input) == 1)
    {
      pilhaDeInteiros.empilha(input);
    }
  }

  mergeSort(pilhaDeInteiros.toArray(), 0, pilhaDeInteiros.topo());
  
  pilhaDeInteiros.print();

  return 0;
}

void mergeSort(int* arr, int inicio, int fim)
{
  if (fim - inicio >= 1)
  {
    int meio = (inicio + fim) / 2;

    mergeSort(arr, inicio, meio);
    mergeSort(arr, meio + 1, fim);
    merge(arr, inicio, meio, fim);
  }
}

void merge(int* arr, int inicio, int meio, int fim)
{
  int left = inicio, right = meio + 1, aux = inicio;
  int *tempArr = (int *)malloc((fim + 1) * sizeof(int));

  while (left <= meio && right <= fim)
  {
    int leftElement = arr[left];
    int rightElement = arr[right];

    if (leftElement <= rightElement)
    {
      tempArr[aux] = leftElement;
      left++, aux++;
    }
    else
    {
      tempArr[aux] = rightElement;
      right++, aux++;
    }
  }

  while (left <= meio)
  {
    tempArr[aux] = arr[left];
    left++, aux++;
  }

  while (right <= fim)
  {
    tempArr[aux] = arr[right];
    right++, aux++;
  }

  for (int i = inicio; i <= fim; i++)
  {
    arr[i] = tempArr[i];
  }

  free(tempArr);
}

void printArray(int arr[], int tam)
{
  cout << "[ ";
  for (int i = 0; i < tam; i++)
  {
    cout << arr[i];
    if (i != tam - 1)
    {
      cout << ", ";
    }
  }
  cout << " ]" << endl;
}