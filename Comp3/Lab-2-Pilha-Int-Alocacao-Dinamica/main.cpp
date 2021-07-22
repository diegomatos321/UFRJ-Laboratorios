#include <iostream>

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
  int atual = -1;
  int tamanhoDaPilha;
  int *pilha;

public:
  PilhaInt(int capacidade = 10);
  PilhaInt(const PilhaInt &pilhaRef);
  ~PilhaInt();

  void empilha(int valor);
  int desempilha();
  int capacidade() const;
  void redimensiona(int n);
  void print(ostream &o);

  PilhaInt &operator<<(int valor);
  const PilhaInt &operator=(const PilhaInt &pilha);
};

PilhaInt::PilhaInt(int capacidade)
{
  tamanhoDaPilha = capacidade;
  pilha = (int*)malloc(tamanhoDaPilha * sizeof(int));

  for (int i = 0; i < tamanhoDaPilha; i++)
  {
    pilha[i] = 0;
  }
}

PilhaInt::PilhaInt(const PilhaInt &pilhaRef)
{
  tamanhoDaPilha = pilhaRef.capacidade();
  pilha = (int*)malloc(tamanhoDaPilha * sizeof(int));

  for (int i = 0; i < tamanhoDaPilha; i++)
  {
    pilha[i] = pilhaRef.pilha[i];
  }

  atual = pilhaRef.atual;
}

PilhaInt::~PilhaInt()
{
  free(pilha);
}

void PilhaInt::empilha(int valor)
{
  if (++atual < tamanhoDaPilha)
  {
    pilha[atual] = valor;
  }
  else
  {
    atual--;
    redimensiona(2 * tamanhoDaPilha);
    empilha(valor);
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

int PilhaInt::capacidade() const
{
  return tamanhoDaPilha;
}

void PilhaInt::redimensiona(int novoTamanho)
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

    if (novoTamanho < atual + 1)
    {
      atual = novoTamanho - 1;
    }

    tamanhoDaPilha = novoTamanho;
  }
  else
  {
    puts ("Error (re)allocating memory");
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
  const int novaCapacidade = operadorParaAtribuir.capacidade();

  redimensiona(novaCapacidade);
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
  // teste1();
  // teste2();
  // teste4();
  // teste5();
  // teste7();
  teste8();
  return 0;
}

void teste1() 
{
  PilhaInt p;

  p.empilha( 1 );
  p << 3 << 9 << 13 << 89;

  cout << p.desempilha() << endl;
  cout << p.desempilha() << endl;

  p.print( cout );
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

  a.print( cout ); 
  cout << endl;

  b.print( cout ); 
  cout << endl;

  c.print( cout ); 
  cout << endl;
}

void teste5()
{
  PilhaInt a{7}, b{500000}, c{5};

  a << 8 << 3 << 1 << 4 << 5;

  for( int i = 0; i < b.capacidade(); i++ )
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

  a.redimensiona( 81 ); 
  cout << a.capacidade() << endl;

  a.redimensiona( 11 ); 
  cout << a.capacidade() << endl;

  a.redimensiona( 6 );
  cout << a.capacidade() << endl;

  a.print( cout ); 
  cout << endl;

  a.redimensiona( 3 ); 
  cout << a.capacidade() << endl;

  a.print( cout ); 
  cout << endl;
}

void teste8()
{
  PilhaInt a{3};

  for( int i = 0; i < 20; i++ ) 
  {
    a << i;
    cout << a.capacidade() << " ";
  }

  cout << endl;

  a.print( cout ); 
  cout << endl;
}
