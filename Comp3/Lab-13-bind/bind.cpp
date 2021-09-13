#include <iostream>
#include <tuple>

using namespace std;

template<typename Functor, typename... Argumentos>
class Bind;

template<typename Functor, typename... Argumentos>
auto bind(Functor lambda, Argumentos... argumentos) {
  return Bind<Functor, Argumentos...>(lambda, argumentos...);
}

template<typename Functor, typename... Parametros, typename... Argumentos>
auto bind(const Bind<Functor, Parametros...>& bind, Argumentos... argumentos) {
  tuple<Argumentos...> tupleArgumentos = make_tuple(argumentos...);
  tuple<Parametros..., Argumentos...> concatenaParametros = tuple_cat(bind.getArgs(), tupleArgumentos);

  return Bind<Functor, Parametros..., Argumentos...>(bind.getFunctor(), concatenaParametros);
}

template<typename Functor, typename... Parametros>
class Bind {
  private:
    Functor lambda;
    tuple<Parametros...> argumentos;

  public:
    Bind(Functor expressao, Parametros... args): lambda(expressao), argumentos(args...) {}
    Bind(Functor expressao, tuple<Parametros...> args): lambda(expressao), argumentos(args) {}

    tuple<Parametros...> getArgs() const {
      return argumentos;
    }

    Functor getFunctor() const {
      return lambda;
    }

    template<typename... UltimosParametros>
    auto operator () (UltimosParametros... ultimosParametros) {
			tuple<UltimosParametros...> tempTuple(ultimosParametros...);
			tuple<Parametros..., UltimosParametros...> tupleFinal = tuple_cat(argumentos, tempTuple);

      if constexpr(is_invocable_v<Functor, Parametros..., UltimosParametros...>) {
        return apply(lambda, tupleFinal);
      } else {
        return Bind<Functor, Parametros..., UltimosParametros...>(lambda, tupleFinal);
      }
    }

    auto call() const {
      return apply(lambda, argumentos);
    }
};