#include <iostream>

#include "otimizador.cpp"

using namespace std;

void teste1();
void teste2();
void teste4();

int main() {
  // teste1();
  // teste2();
  teste4();

  return EXIT_SUCCESS;
}

void teste1() {
  Matriz<10,20> a;
  Matriz<20,3> b;

  auto c = a*b;
  
  auto f = Apply( []( double x ){ return rand(); } );
  
  c = f(c);
  auto d = f(a) * b;
  
  for( int i = 0; i < d.nLin(); i++ )
    for( int j = 0; j < d.nCol(); j++ )
      cout << d[i][j] << endl;
}

void teste2() {
  Matriz<100,1> a;
  Matriz<1,100> b;

  auto x = a * b;
  auto y = b * a;
}

void teste4() {
  Matriz<1000,1> a;
  Matriz<1,1000> b;
  Matriz<1000,1000> c;
  int tempo = 0, lapso1, lapso2;

  tempo = clock();

  Matriz<1000,1000> x1 = a * b;
  Matriz<1000,1000> x2 = x1 * c;

  // cout << tamanho(x1) << endl;
  // cout << tamanho(x2) << endl;

  lapso1 = clock() - tempo;

  tempo = clock();

  Matriz<1000,1000> y = a * b * c;

  lapso2 = clock() - tempo;
  // cout << tamanho(y) << endl;

  if( lapso1/lapso2 > 10 )
    cout << "Otimizou" << endl;
  else
    cout << "Não otimizou" << endl;
}