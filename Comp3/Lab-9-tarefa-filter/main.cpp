#include <iostream>
#include <string>
#include <vector>

#include "filter.cpp"

using namespace std;

void teste1();

template<typename T>
void print(T x) {
  cout << x << endl;
}

int main() {
  teste1();
  
  return 0;
}

void teste1() {
  vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
  auto result = v1 | []( int x ) { return x % 2 == 0; };
  for( auto x : result )
      cout << x << " ";
}