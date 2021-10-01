#include <iostream>

#include "lambda.cpp"

using namespace std;

void exemplo();
void teste1();
void teste2();
void teste3();
void teste4();

int main() {
  teste1();
  teste2();
  teste3();
  teste4();
}

void exemplo() {
  auto s = x + x + x;
  cout << s( 8 );
}

void teste1() {
  vector<int> v1 = { 1, 2, 3, 4, 1, 1, 0, 8 };
  v1 | (x % 2 == 0) | cout << x*x + 1 << ' ';
}

void teste2() {
  int v1[] = { 1, 2, 3, 4, 1, 1, 0, 8 };
  v1 | (x % 2 == 0) | cout << x*x + 1 << ' ';
}

void teste3() {
  int v1[] = { 1, 2, 3, 4, 1, 1, 0, 8 };
  v1 | (x % 2 == 1) | x*x | cout << x << ' ';
}

void teste4() {
  string v1[] = { "a", "b2", "cc3", "saci" };
  v1 | []( string n ) { return n.length() % 2 == 0; } | (x+x) | cout << x << ' ';
}