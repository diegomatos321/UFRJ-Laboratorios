#include <iostream>
#include <cstdlib>
#include <ctime>

#define TAM 10

using namespace std;

void mergeSort(int arr[], int inicio, int fim);
void merge(int arr[], int inicio, int meio, int fim);
void printArray(int arr[], int tam);

int main()
{
  srand(time(NULL));

  int listaDeInteiros[TAM];
  for (unsigned i = 0; i < TAM; i++)
  {
    listaDeInteiros[i] = rand() % 10 + 1;
  }
  
  cout << "Unordered" << endl;
  printArray(listaDeInteiros, TAM);

  mergeSort(listaDeInteiros, 0, TAM-1);

  cout << "Ordered" << endl;
  printArray(listaDeInteiros, TAM);

  return 0;
}

void mergeSort(int arr[], int inicio, int fim)
{
  if (fim - inicio >= 1)
  {
    int meio = (inicio + fim) / 2;

    mergeSort(arr, inicio, meio);
    mergeSort(arr, meio + 1, fim);
    merge(arr, inicio, meio, fim);
  }
}

void merge(int arr[], int inicio, int meio, int fim)
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