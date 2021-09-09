#include <iostream>
#include <tuple>

using namespace std;

template<typename Functor, typename ...Parametros>
class Bind;

template<typename Functor, typename ...Parametros>
auto bind(Functor lambda, Parametros... argumentos) {
  return Bind<Functor, Parametros...>(lambda, argumentos...);
}

template<typename Functor, typename ...Parametros>
class Bind {
  private:
    Functor lambda;
    tuple<Parametros...> argumentos;

  public:
    Bind(Functor expressao, Parametros... args): lambda(expressao), argumentos(args...) {}

    template<typename ParametroFinal>
    auto operator () (ParametroFinal ultimoArgumento) {
			tuple<ParametroFinal> tempTuple(ultimoArgumento);
			tuple<Parametros..., ParametroFinal> tupleFinal = tuple_cat(argumentos, tempTuple);

      return apply(lambda, tupleFinal);
    }
};

/* template <typename Functor, typename ...Argumentos>
ostream& operator << (ostream& cout, const Bind<F, A...>& bind) {
	return cout << bind.call();
} */