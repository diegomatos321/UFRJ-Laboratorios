#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include "Var.cpp"

using namespace std;

int main() {
  Var a, b;
  
  cout << a << endl; // saída: "undefined"
  a = 1;
  cout << a << endl; // saída: 1
  a = "hello";
  cout << a << endl; // saída: hello
  
  a = newObject();
  a["atr"] = 9;
  a["metodo"] = []( auto x ){ return x*x; };
  b = 4;
  cout << a["metodo"]( b ) << endl; // Saída: 16;
}