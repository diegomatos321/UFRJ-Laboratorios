#include <iostream>
#include <string>
#include <vector>

#include "stream.cpp"

using namespace std;

template<typename T>
void print(T x) {
  cout << x << endl;
}

int main() {
  int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
  vector<int> v{ 2 , 6, 8 };
  string frase = "Diego Matos";

  tab | []( int x ) { cout << x*x << endl; };
  tab | [ &v ]( int x ) { v.push_back( x ); };
  v | []( int x ) { cout << x*x << endl; };
  v | &print;
  frase | &print;

  return 0;
}