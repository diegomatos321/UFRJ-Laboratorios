#include <iostream>

using namespace std;

class PilhaInt
{
private:
  int atual = -1;
  unsigned int tamanhoDaPilha;
  int *pilha;

public:
  PilhaInt(unsigned int capacidade = 10);
  PilhaInt(const PilhaInt &pilhaRef);

  void empilha(int valor);
  int desempilha();
  unsigned int capacidade() const;
  void redimensiona(unsigned int n);
  void print(ostream &o);

  PilhaInt &operator<<(int valor);
  const PilhaInt &operator=(const PilhaInt &pilha);
};

PilhaInt::PilhaInt(unsigned int capacidade)
{
  tamanhoDaPilha = capacidade;
  pilha = (int*)malloc(tamanhoDaPilha * sizeof(int));

  for (unsigned int i = 0; i < tamanhoDaPilha; i++)
  {
    pilha[i] = 0;
  }
}

PilhaInt::PilhaInt(const PilhaInt &pilhaRef)
{
  tamanhoDaPilha = pilhaRef.capacidade();
  pilha = (int*)malloc(tamanhoDaPilha * sizeof(int));

  for (unsigned int i = 0; i < tamanhoDaPilha; i++)
  {
    pilha[i] = pilhaRef.pilha[i];
  }

  atual = pilhaRef.atual;
}

void PilhaInt::empilha(int valor)
{
  if (atual < (int)tamanhoDaPilha)
  {
    atual++;
    pilha[atual] = valor;
  }
  else
  {
    cout << "Error !" << endl;
  }
}

int PilhaInt::desempilha()
{
  if (atual >= 0)
  {
    int valorRetirado = pilha[atual];
    pilha[atual] = 0;
    atual--;

    return valorRetirado;
  }
  else
  {
    cout << "Error !" << endl;
    return -1;
  }
}

unsigned int PilhaInt::capacidade() const
{
  return tamanhoDaPilha;
}

void PilhaInt::redimensiona(unsigned int novoTamanho)
{
  int *novaPilha;

  if (tamanhoDaPilha != novoTamanho)
  {
    tamanhoDaPilha = novoTamanho;
  }

  novaPilha = (int *)realloc(pilha, tamanhoDaPilha * sizeof(int));

  if (novaPilha != NULL)
  {
    pilha = novaPilha;
    free(novaPilha);
  }
  else
  {
    free(pilha);
    free(novaPilha);
    exit(1);
  }
}

PilhaInt &PilhaInt::operator << (int valor)
{
  empilha(valor);

  return *this;
}

const PilhaInt &PilhaInt::operator = (const PilhaInt &operadorParaAtribuir)
{
  redimensiona(operadorParaAtribuir.capacidade());
  atual = operadorParaAtribuir.atual;

  for (int i = 0; i <= atual; i++)
  {
    pilha[i] = operadorParaAtribuir.pilha[i];
  }

  return *this;
}

void PilhaInt::print(ostream &o)
{
  o << "[ ";
  for (int i = 0; i <= atual; i++)
  {
    o << pilha[i];

    if (i == atual)
    {
      break;
    }

    o << ", ";
  }
  o << " ]";
}

int main()
{
  PilhaInt pilha1;
  pilha1.empilha(12);
  pilha1.empilha(7);
  pilha1.empilha(8);
  pilha1.empilha(33);
  
  
  cout << "Pilha 1: " << endl;
  pilha1.print(cout);
  cout << endl;
  
  PilhaInt pilha2(pilha1);

  cout << "Pilha 2: " << endl;
  pilha2.print(cout);
  cout << endl;

  pilha2.empilha(-12);
  pilha2.empilha(-5);
  pilha2.empilha(100);

  PilhaInt pilha3;
  pilha3 = pilha2;

  cout << "Pilha 3: " << endl;
  pilha3.print(cout);
  cout << endl;

  return 0;
}