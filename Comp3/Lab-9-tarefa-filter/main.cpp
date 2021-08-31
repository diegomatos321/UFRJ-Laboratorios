#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>

#include "filter.cpp"

using namespace std;

void teste1();
void teste2();
void teste3();
void teste4();

template<typename T>
void print(T x) {
  cout << x << endl;
}

int main() {
  teste1();
  // teste2();
  // teste3();
  // teste4();

  return 0;
}

void teste1() {
  vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
  auto result = v1 | []( int x ) { return x % 2 == 0; };
  for( auto x : result )
      cout << x << " ";
}

void teste2() {
  vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
  v1 | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << " "; };
}

void teste3() {
  int v1[] = { 2, 9, 8, 8, 7, 4 };
  auto result = v1 | []( int x ) { return x % 2 == 0; };
  for( auto x : result )
    cout << x << " ";
}

void teste4() {
  int v1[] = { 2, 9, 8, 8, 7, 4 };
  v1 | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << " "; };
}