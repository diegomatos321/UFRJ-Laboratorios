#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <iterator>
#include <functional>

using namespace std;

class Indice {
  private:
    int indice = 0;
  
  public:
    Indice(int i): indice(i) {}

    template <typename Iteravel>
    auto operator () (const Iteravel& iteravel = 0) const {
      return iteravel[indice];
    }
};

template <typename Functor>
class Lambda {
  private:
    Functor functor;

  public:
    Lambda (Functor lambda): functor(lambda) {}

    template <typename Value>
    Functor operator()(Value valor = 0) const {
      return f(valor);
    }

    Indice operator[] (int linha) {
      return Indice(linha);
    }
};

class Cte {
  public:
    template<typename Generico>
    Generico operator() (const Generico generico) const {
      return generico;
    }
};

template <typename TipoA, typename TipoB>
class Desigualdade {
  private:
    TipoA tipoA;
    TipoB tipoB;

  public:
    Desigualdade(TipoA a, TipoB b): tipoA(a), tipoB(b) {}

    bool operator () () {
      
    }
}

template<typename Iteravel, typename Functor>
auto operator | (const Iteravel& iteravel, Functor lambda) {
  if constexpr(is_same_v<invoke_result_t<Functor, decltype(*begin(iteravel))>, bool> == true) {
    vector<decay_t<decltype(*begin(iteravel))>> tempVetor;

    for (auto x : iteravel) {
      if (invoke(lambda, x)) {
        tempVetor.push_back(x);
      }
    }

    return tempVetor;
  } else if constexpr(is_same_v<invoke_result_t<Functor, decltype(*begin(iteravel))>, void> == false) {
    vector<decay_t<invoke_result_t<Functor, decltype(*begin(iteravel))>>> tempVetor;

    for (auto x : iteravel) {
      tempVetor.push_back(invoke(lambda, x));
    }

    return tempVetor;
  } else {
    for (auto x : iteravel) {
      invoke(lambda, x);
    }
  }
}