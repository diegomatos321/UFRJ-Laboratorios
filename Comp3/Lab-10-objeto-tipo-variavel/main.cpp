#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <type_traits>
#include <functional>

#include "Var.cpp"

using namespace std;

void teste1();

/* Var print( const Var& o ) {
  cout << "{ nome: " << o["nome"]
       << ", idade: " << o["idade"]( o )
       << ", nascimento: " << o["nascimento"]
       << ", print: " << o["print"] 
       << ", atr: " << o["atr"] 
       << " }" << endl;
       
  return Var();     
} */

/* void imprime( Var v ) {
    v["print"]( v );
} */

int main( int argc, char* argv[] ) try {     
  teste1();

  return 0;
} catch( Var::Erro e ) {
  cout << "Erro fatal: " << e() << endl;
}

void teste1() {
  Var a, b;
/*   b = 10;
  cout << a << " " << b << endl;
  a = 3.14; */
  b = "uma string";
  cout /* << a << " " */ << b << endl;
}