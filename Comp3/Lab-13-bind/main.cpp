#include <iostream>

using namespace std;

#include "bind.cpp"

int mdc( int a, int b ) { return b == 0 ? a : mdc( b, a%b ); }

int main() {
  auto f = bind( mdc, 12 ); 
  cout << f( 9 ) << endl;

  return 0;
}