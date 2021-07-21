#include <iostream>

#define TAMANHO_MAXIMO_PILHA 20

using namespace std;

class PilhaInt
{
private:
  int atual = -1;
  int pilha[TAMANHO_MAXIMO_PILHA];

public:
  PilhaInt();

  void empilha(int valor);
  int desempilha();
  void print(ostream &o);
  PilhaInt &operator << (int valor);
  const PilhaInt &operator = (const PilhaInt& pilha);
};

PilhaInt::PilhaInt()
{
  for (unsigned int i = 0; i < TAMANHO_MAXIMO_PILHA; i++)
  {
    pilha[i] = 0;
  }
}

void PilhaInt::empilha(int valor)
{
  if (atual < TAMANHO_MAXIMO_PILHA)
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

PilhaInt& PilhaInt::operator << (int valor)
{
  empilha(valor);

  return *this;
}

const PilhaInt& PilhaInt::operator = (const PilhaInt& operadorParaAtribuir)
{
  atual = operadorParaAtribuir.atual;

  for (unsigned int i = 0; i <= atual; i++)
  {
    pilha[i] = operadorParaAtribuir.pilha[i];
  }
  
  return *this;
}

void PilhaInt::print(ostream &o)
{
  o << "[ ";
  for (unsigned int i = 0; i <= atual; i++)
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
  PilhaInt p, q;

  q << 2;
  p << 19 << 18 << 17 << 30;

  q = p;
  p.desempilha();
  q << 7;

  p.print( cout );
  q.print( cout );

  // cout << "q = " << ssq.str() << "\n" << "p = " << ssp.str() << endl;

  // Essa linha é apenas para gerar um erro se o "operator=" não for definido. Ignore-a!
  // auto l = &PilhaInt::operator=; (p.*l)(q);
}