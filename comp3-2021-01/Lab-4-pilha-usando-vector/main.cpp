#include <iostream>
#include <vector>

using namespace std;

void teste1();
void teste2();
void teste4();
void teste5();
void teste7();
void teste8();

class PilhaInt
{
private:
  vector<int> pilha;

public:
  PilhaInt();
  PilhaInt(int capacidade);
  PilhaInt(const PilhaInt &pilhaRef);

  void empilha(int valor);
  int desempilha();
  int capacidade() const;
  void redimensiona(int n);
  void print(ostream &o);

  PilhaInt &operator<<(int valor);
  const PilhaInt &operator=(const PilhaInt &pilha);
};

PilhaInt::PilhaInt() {}

PilhaInt::PilhaInt(int capacidade)
{
  pilha.reserve(capacidade);
}

PilhaInt::PilhaInt(const PilhaInt &pilhaRef) : pilha(pilhaRef.pilha) {}

void PilhaInt::empilha(int valor)
{
  pilha.push_back(valor);
}

int PilhaInt::desempilha()
{
  int aux = pilha.back();
  pilha.pop_back();

  return aux;
}

int PilhaInt::capacidade() const
{
  return pilha.capacity();
}

void PilhaInt::redimensiona(int novoTamanho)
{
  if (capacidade() == novoTamanho)
  {
    return;
  }

  pilha.resize(novoTamanho);
  pilha.shrink_to_fit();
}

PilhaInt &PilhaInt::operator<<(int valor)
{
  empilha(valor);

  return *this;
}

const PilhaInt &PilhaInt::operator=(const PilhaInt &operadorParaAtribuir)
{
  redimensiona(operadorParaAtribuir.capacidade());
  pilha = operadorParaAtribuir.pilha;

  return *this;
}

void PilhaInt::print(ostream &o)
{
  o << "[ ";
  for (unsigned int i = 0; i < pilha.size(); i++)
  {
    o << pilha[i];

    if (i == pilha.size() - 1)
    {
      break;
    }

    o << ", ";
  }
  o << " ]";
}

int main()
{
  // teste1();
  // teste2();
  // teste4();
  // teste5();
  // teste7();
  // teste8();
  return 0;
}

void teste1()
{
  PilhaInt p;

  p.empilha(1);
  p << 3 << 9 << 13 << 89;

  cout << p.desempilha() << endl;
  cout << p.desempilha() << endl;

  p.print(cout);
}

void teste2()
{
  PilhaInt a(5), b(15);

  cout << a.capacidade() << endl;
  cout << b.capacidade() << endl;
}

void teste4()
{
  PilhaInt a{7}, b{500}, c{5};

  a << 8 << 3 << 1 << 4 << 5;
  b << 1 << 2 << 3;

  c = a;
  a = b;
  b = c;

  c.desempilha();
  c << 7;

  a.print(cout);
  cout << endl;

  b.print(cout);
  cout << endl;

  c.print(cout);
  cout << endl;
}

void teste5()
{
  PilhaInt a{7}, b{5000}, c{5};

  a << 8 << 3 << 1 << 4 << 5;

  for (int i = 0; i < b.capacidade(); i++)
    b << i;

  c = a;
  a = b;
  b = c;

  cout << a.capacidade() << ", " << b.capacidade() << ", " << c.capacidade() << endl;
}

void teste7()
{
  PilhaInt a{81};

  a << 5 << 6 << 3 << 2 << 9 << 13;

  a.redimensiona(81);
  cout << a.capacidade() << endl;

  a.redimensiona(11);
  cout << a.capacidade() << endl;

  a.redimensiona(6);
  cout << a.capacidade() << endl;

  a.print(cout);
  cout << endl;

  a.redimensiona(3);
  cout << a.capacidade() << endl;

  a.print(cout);
  cout << endl;
}

void teste8()
{
  PilhaInt a{3};

  for (int i = 0; i < 20; i++)
  {
    a << i;
    cout << a.capacidade() << " ";
  }

  cout << endl;

  a.print(cout);
  cout << endl;
}
