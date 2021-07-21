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
    void print_msg(ostream &o, const char *msg);
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
  else{
    print_msg(cout, "Erro!!");
    // cout << "Error !" << endl;
  }
}

int PilhaInt::desempilha() 
{
  if (atual > 0)
  {
    int valorRetirado = pilha[atual];
    pilha[atual] = 0;
    atual--;

    return valorRetirado;
  }
  else
  {
    print_msg(cout, "Erro!!");
    // cout << "Error !" << endl;
    return -1;
  }
}

void print_msg(ostream &o, const char *msg) 
{
  o << msg << endl;
}

int main() 
{
  PilhaInt pilha1;

  pilha1.empilha(1);
  pilha1.empilha(12);
  pilha1.empilha(5);
  pilha1.empilha(7);

  cout << pilha1.desempilha() << endl;

  return 0;
}