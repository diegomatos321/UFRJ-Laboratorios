#include <iostream>

using namespace std;

#include "bind.cpp"

void teste1();
// void teste2();

int mdc( int a, int b ) { return b == 0 ? a : mdc( b, a%b ); }

int main() {
  teste1();
  // teste2();

  return 0;
}

void teste1() {
  auto f1 = bind( mdc, 12 );
  for( int i = 2; i <= 12; i++ )
    cout << f1( i ) <<  " ";
}

/* void teste2() {
  auto f2 = bind( mdc );
  auto f1 = bind( f2, 12 );
  for( int i = 2; i <= 12; i++ )
    cout << f1( i ) <<  " ";
} */