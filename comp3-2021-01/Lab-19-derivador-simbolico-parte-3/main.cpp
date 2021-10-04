#include <iostream>
#include <assert.h>

#include "derivador.cpp"

using namespace std;

void teste1();
// void teste2();
// void teste3();
// void teste4();
// void teste8();
// void teste9();
// void teste11();
// void teste12();

int main() {
  teste1();
  // teste2();
  // teste3();
  // teste4();
  // teste8();
  // teste9();
  // teste11();
  // teste12();

  return 0;
}

void teste1() {
  // auto f = 3.0 + x + x;
  auto f = 3.0 + x * x;
  // auto f = 3.0 + x + x;

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
}

void teste2() {
  // auto f = x * x;
  auto f = 0 * x;
  // auto f = 1 * x;

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
}

/* void teste3() {
  auto f = x - (x - 5.0);

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
}

void teste4() {
  auto f = x->*3;

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
}

void teste8() {
  auto f = 1.0 / (sin(x)->*2 + cos(x)->*2)->*4;

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
}

void teste9() {
  auto f = exp( x * log( x - 8.0 ) + 1.0 );

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
}

void teste11() {
  auto f = log( x->* 4 + 8.0 ) * sin( cos( x / 3.14 ) );

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
}

void teste12() {
  auto f = log( (8.1/(x+1.0)->*3 - 9.2 ) * (x + 3) *sin( cos( x / 3.14 ) ));

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
} */