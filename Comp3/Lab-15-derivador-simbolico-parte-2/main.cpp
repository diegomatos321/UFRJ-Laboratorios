#include <iostream>

#include "derivador.cpp"

using namespace std;

void teste1();


int main() {
  teste1();


  return 0;
}

void teste1() {
  double v = 5.1;
  auto f = 3.0 * x * x;

  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}