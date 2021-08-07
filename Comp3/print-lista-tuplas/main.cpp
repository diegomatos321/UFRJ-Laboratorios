#include <iostream>
#include <initializer_list>
#include <vector>
#include <memory>

using namespace std;

class AbstractPair {
  public:
    virtual void imprime(ostream& o){};
    virtual ~AbstractPair(){};
};

template <typename TipoA, typename TipoB>
class ImplPair: public AbstractPair {
  public:
    ImplPair(TipoA novaChave, TipoB novoValor){
      chave = novaChave;
      valor = novoValor;
    }

    virtual void imprime(ostream& o) {
      o << chave << " = " << valor << endl;
    }
  
  private:
    TipoA chave;
    TipoB valor;
};

class Pair {
  public:
    template <typename TipoA, typename TipoB>
    Pair( TipoA a, TipoB b ) {
      p = new ImplPair<TipoA, TipoB>(a, b);
    }

    void imprime(ostream& o) const {
      p -> imprime(o);
    }

    ~Pair() {
      delete p;
    }
  
  private:
    AbstractPair *p;
};

void print( ostream& o, initializer_list<Pair> lista ) {
  for (const Pair& par : lista) {
    par.imprime(o);
  }
}

int main() {
  Pair p{ "1", "2" };
  print( cout, { { "jan", 1 }, { string( "pi" ), 3.14 }, p } );

  return 0;
}