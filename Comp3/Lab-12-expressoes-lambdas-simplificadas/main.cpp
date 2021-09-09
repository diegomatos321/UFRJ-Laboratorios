#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>

#include "lambda.cpp"

using namespace std;

void teste1();

int main() {
  teste1();
}

void teste1() {
  vector<int> v1 = { 1, 2, 3, 4, 1, 1, 0, 8 };
  v1 | (x % 2 == 0) | cout << x*x + 1 << ' ';
}
