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
void teste2();
void teste4();

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
  // teste1();
  // teste2();
  // teste3();
  teste4();

  return 0;
} catch( Var::Erro e ) {
  cout << "Erro fatal: " << e() << endl;
}

void teste1() {
  Var a, b = 10;
  cout << a << " " << b << endl;
  a = 3.14;
  b = "uma string";
  cout << a << " " << b << endl;
}

void teste2() {
  Var a;
  a = 3;
  cout << a["mes"] << endl;
}

void teste3() {
  Var a;
  a = newObject();
  cout << a(5) << endl;
}

void teste4() {
  Var a[5] = { true, 'X', 2, 2.1, "abracadabra" };
  Var b = 200, c = 300.1, d = "palavra ";
  for( auto& x: a ) {
    cout << x+b << "," << x+c << "," << x+d << "," << 3 / x << "," << 1.1 * x << ","
        << Var(x && true) << "," << Var(x && false) <<  "," << Var(b >= x) << "," << Var(x < d) << endl;
  }
}