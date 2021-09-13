#include <iostream>

using namespace std;

#include "bind.cpp"

void teste1();
void teste2();
void teste4();
void teste5();
void teste7();

// long mdc( long a, long b ) { return b == 0 ? a : mdc( b, a%b ); }
int mdc( int a, int b ) { return b == 0 ? a : mdc( b, a%b ); }

struct MMC {
  auto operator()( long a, long b ) { return a*b/mdc(a,b); }    
};

int main() {
  teste1();
  teste2();
  teste4();
  teste5();
  teste7();

  return 0;
}

void teste1() {
  auto f1 = bind( mdc, 12 );
  for( int i = 2; i <= 12; i++ )
    cout << f1( i ) <<  " ";
}

void teste2() {
  auto f2 = bind( mdc );
  auto f1 = bind( f2, 12 );
  for( int i = 2; i <= 12; i++ )
    cout << f1( i ) <<  " ";
}

void teste4() {
  auto f2 = bind( []( int x, int y, int z ){ cout << x*y << (char) z << " " ; }, 10 );
  for( int i = 0; i < 5; i++ )
    f2( i, ',' );
}

void teste5() {
  auto f3 = bind( []( int x, int y, int z ){ cout << x*z << (char) y << " " ; } );
  auto f1 = f3( 5, ';' );
  for( int i = 0; i < 5; i++ )
    f1( i );
}

void teste7() {
  MMC mmc;
  auto f2 = bind( mmc );
  auto f1 = f2( 6 );
  for( int i = 2; i <= 12; i++ )
    cout << f1( i ) << " ";
}