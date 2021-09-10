#include <iostream>

#include "derivador.cpp"

using namespace std;

void teste1();
void teste2();
void teste3();
void teste4();
void teste5();

int main() {
  // teste1();
  // teste2();
  // teste3();
  // teste4();
  teste5();

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