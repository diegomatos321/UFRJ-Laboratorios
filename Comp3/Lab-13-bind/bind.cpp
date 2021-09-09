#include <iostream>

using namespace std;

template<typename Functor, typename Parametro>
class Bind;

// TODO: Vários argumentos
template<typename Functor, typename Parametro>
Bind<Functor, Parametro> bind(Functor lambda, Parametro n) {
  return Bind<Functor, Parametro>(lambda, n);
}

template<typename Functor, typename Parametro>
class Bind {
  private:
    Functor lambda;
    Parametro n;

  public:
    Bind(Functor expressao, Parametro argumento): lambda(expressao), n(argumento) {}

    template<typename OutroParametro>
    auto operator () (OutroParametro argumento) {
      return lambda(n, argumento);
    }
};
