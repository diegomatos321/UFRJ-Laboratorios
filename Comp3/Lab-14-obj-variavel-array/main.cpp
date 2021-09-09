#include <iostream>

#include "obj-variavel-arrays.cpp"

using namespace std;

int main() try {
  Var a[]= {  1.9, 'a', true, "oi", [](Var v){ return "Uma função"; } };
 
  for( const auto& x: a )
    cout << x << endl;

  cout << "Soma: " << a[3] + a[1] + "!" << endl;
  cout << "Soma: " << a[0] + a[2] + "!" << endl;
  cout << a[3]( 1 ) << endl;  
}
catch( Var::Erro e ) {
  cout << e() << endl;
} 