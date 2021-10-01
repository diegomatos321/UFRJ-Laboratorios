#include <iostream>

#include "derivador.cpp"

using namespace std;

void teste1();
void teste2();
void teste3();
void teste4();
void teste5();
void teste6();
void teste7();
void teste8();
void teste9();
void teste10();

int main() {
  teste1();
  teste2();
  teste3();
  teste4();
  teste5();
  teste6();
  teste7();
  teste8();
  teste9();
  // teste10();

  return 0;
}

void teste1() {
  double v = 5.1;
  auto f = 3.0 * x * x;

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void teste2() {
  double v = 1.1;
  auto f = x*x*( x + 8.0 ) + x;

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void teste3() {
  double v = 0.5;
  auto f = sin( x * x * cos( 3.14 * x + 1.0 ) );

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void teste4() {
  double v = 3.14;
  auto f = sin( x * x - cos( 3.14 * x + 1.0 ) );

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void teste5() {
  double v = 3.14159;
  auto f =  sin(x)/cos(x);

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void teste6() {
  double v = -7.3;
  auto f = x->*3 + x->*2;

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void teste7() {
  double v = -0.5;
  auto f = 1.0 / (sin(x)->*2 + cos(x)->*2)->*4;

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void teste8() {
  double v = 0.1;
  auto f = 1 / (1 + exp( -2*( x - 1 )->*4 ) );

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void teste9() {
  double v = 3;
  auto f = exp( x * log( x ) );

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

/* void teste10() {
  double v = 3;
  auto f =  2 * x->*1.1;

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
} */