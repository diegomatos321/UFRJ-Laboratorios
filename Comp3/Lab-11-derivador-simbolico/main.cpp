#include <iostream>

#include "derivador.cpp"

using namespace std;

void teste1();

int main() {
  X x;
  Expressao f = x * 3;
  f.print(cout);
  // teste1();

  return 0;
}

/* void teste1() {
  double v = 5.1;
  auto f = 3.0 * x * x;
} */