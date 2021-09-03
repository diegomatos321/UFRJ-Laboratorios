#include <iostream>
#include <initializer_list>
#include <memory>

using namespace std;

class AbstractPair {
  public:
    virtual ~AbstractPair() = default;
    virtual void imprime(ostream& o) const = 0;
};

template <typename TipoA, class TipoB>
class ImplPair: public AbstractPair {
  private:
    TipoA chave;
    TipoB valor;
  
  public:
    ImplPair(TipoA novaChave, const TipoB& novoValor): chave(novaChave), valor(novoValor) {}
    ~ImplPair() {}

    void imprime(ostream& o) const {
      o << chave << " = " << valor << endl;
    }
};

class Pair {
  private:
    shared_ptr<AbstractPair> p;

  public:
    template <typename TipoA, class TipoB>
    Pair(TipoA a, const TipoB& b ): p(new ImplPair<TipoA, TipoB>(a, b)){
    }
    ~Pair() {}

    void imprime(ostream& o) const {
      p -> imprime(o);
    }
};

void print( ostream& o, const initializer_list<Pair>& lista ) {
  for (const Pair& par : lista) {
    par.imprime(o);
  }
}
