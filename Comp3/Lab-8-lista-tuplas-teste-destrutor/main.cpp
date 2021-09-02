#include <iostream>
#include <initializer_list>
#include <memory>

#include "leak.cpp"
#include "tuplas.cpp"

using namespace std;

void teste1();
void teste2();
void teste3();
void teste4();

int main() {
  teste1();
  // teste2();
  // teste3();
  // teste4();

  return 0;
}

void teste1() {
  print( cout, { { "jan", Leak() }, { string( "pi" ), Leak() } } );
}

void teste2() {
  Leak *l = new Leak[2];
  print( cout, { { "jan", l[0] }, { string( "pi" ), l[1] } } );
  delete [] l;
}

void teste3() {
  shared_ptr<Leak> l ( new Leak() );
  print( cout, { { "jan", *l }, { string( "pi" ), *l } } );
}

void teste4() {
  Leak a, b, c;
  vector<Leak> v = { a, b };
  print( cout, { { "v", v }, { "c", c } } );
}