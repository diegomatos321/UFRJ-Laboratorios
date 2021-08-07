#include <iostream>
// #include <vector>

using namespace std;

class AbstractPair {
  public:
    virtual void imprime(ostream& o);
    virtual ~AbstractPair();
};

template <typename TipoA, typename TipoB>
class Pair: AbstractPair {
  public:
    Pair(TipoA novaChave, TipoB novoValor) {
      chave = novaChave;
      valor = novoValor;
    }
  
  private:
    TipoA chave;
    TipoB valor;
};

/* template <typename TipoA, typename TipoB>
AbstractPair makePair(TipoA novaChave, TipoB novoValor) {
  Pair novoPair<TipoA, TipoB>(novaChave, novoValor);
  return novoPair;
} */

void print( ostream& o, initializer_list<Pair> lista ) {
  for (Pair par: lista) {
    par.imprime(o);
  }
}

int main() {
  // vector<AbstractPair> listaDePares;

/*   AbstractPair p1 = makePair("Janeiro", 1);
  AbstractPair p2 = makePair("Fevereiro", 2);
  AbstractPair p3 = makePair("Março", 3); */

  print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

  return 0;
}