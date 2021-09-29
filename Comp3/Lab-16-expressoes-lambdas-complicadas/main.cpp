#include <iostream>

#include "expressoes-lambdas-complicadas.cpp"

using namespace std;

void teste1();
// void teste2();
// void teste3();
// void teste4();

int main() {
  teste1();
}

void teste1() {
  vector< vector<int> > m{ { 1, 2, 3 }, { 0, 3, 7 }, { 1, 3 } };
  m | []( auto v ) { return v[0] != 0; } | [x]( auto v ) { v + 7 | cout << x << ' '; };
}