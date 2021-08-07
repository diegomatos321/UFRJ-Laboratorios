#include <iostream>

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

    void imprime(ostream& o) {
      p -> imprime(o);
    }

    ~Pair() {
      delete p;
    }
  
  private:
    AbstractPair *p;
};

void print( ostream& o, initializer_list<Pair> lista ) {
  for (Pair par: lista) {
    par.imprime(o);
  }
}

int main() {

  print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

  return 0;
}