#include <iostream>

using namespace std;

void mergeSort(int arr[], int inicio, int fim);
void merge(int arr[], int inicio, int meio, int fim);

int main()
{
  int listaDeInteiros[] = {9, 7, 3, 6, 2};

  for (int i = 0; i < 5; i++)
  {
    cout << "Unordered" << endl;
    cout << "[ " << listaDeInteiros[i] << " ]" << endl;
  }

  mergeSort(listaDeInteiros, 0, 5);

  for (int i = 0; i < 5; i++)
  {
    cout << "Ordered" << endl;
    cout << "[ " << listaDeInteiros[i] << " ]" << endl;
  }
  
  return 0;
}

void mergeSort(int arr[], int inicio, int fim)
{
  if (fim - inicio > 1)
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
  int* tempArr = (int*) malloc((fim) * sizeof(int));

  while (left <= meio && right < fim)
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