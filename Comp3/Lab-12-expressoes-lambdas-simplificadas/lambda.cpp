#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

class X {
  public:
    template <typename Generico>
    Generico operator() (const Generico generico) const {
      return generico;
    }
};

template <typename Tipo> 
class Cte {
  private:
    Tipo constante;

  public:
    Cte(Tipo valor): constante(valor) {}

    template<typename Generico>
    Tipo operator() (const Generico generico) const {
      return constante;
    }
};

template <typename TipoA, typename TipoB> 
class Soma {
  private:
    TipoA tipoA;
    TipoB tipoB;
  
  public:
    Soma(TipoA valorA, TipoB valorB): tipoA(valorA), tipoB(valorB) {}

    template<typename Generico>
    auto operator() (const Generico generico) const {
      return tipoA(generico) + tipoB(generico);
    }
};

template <typename TipoA, typename TipoB> 
class Produto {
  private:
    TipoA tipoA;
    TipoB tipoB;
  
  public:
    Produto(TipoA valorA, TipoB valorB): tipoA(valorA), tipoB(valorB) {}

    template<typename Generico>
    auto operator() (const Generico generico) const {
      return tipoA(generico) * tipoB(generico);
    }
};

template <typename TipoA, typename TipoB> 
class Modulo {
  private:
    TipoA tipoA;
    TipoB tipoB;
  
  public:
    Modulo(TipoA valorA, TipoB valorB): tipoA(valorA), tipoB(valorB) {}

    template<typename Generico>
    auto operator() (const Generico generico) const {
      return tipoA(generico) % tipoB(generico);
    }
};

template <typename TipoA, typename TipoB> 
class Igual {
  private:
    TipoA tipoA;
    TipoB tipoB;
  
  public:
    Igual(TipoA valorA, TipoB valorB): tipoA(valorA), tipoB(valorB) {}

    template<typename Generico>
    bool operator() (const Generico generico) const {
      return tipoA(generico) == tipoB(generico);
    }
};

template <typename Expressao> 
class Imprime {
  private:
    ostream& output;
    Expressao expressao;
    string resto = "";
  
  public:
    Imprime(ostream& out, Expressao expressao): output(out), expressao(expressao) {}

    template<typename Generico>
    void operator() (Generico generico) const {
      output << expressao(generico) << resto;
    }

    void add(const char c) {
      resto += c;
    }
};

template <typename TipoA, typename TipoB>
auto operator + (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_arithmetic_v<TipoA>)
    return Soma<Cte<TipoA>, TipoB>(tipoA, tipoB);
  else if constexpr(is_arithmetic_v<TipoB>)
    return Soma<TipoA, Cte<TipoB>>(tipoA, tipoB);
  else
    return Soma<TipoA, TipoB>(tipoA, tipoB);
}

template <typename TipoA, typename TipoB>
auto operator * (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_arithmetic_v<TipoA>)
    return Produto<Cte<TipoA>, TipoB>(tipoA, tipoB);
  else if constexpr(is_arithmetic_v<TipoB>)
    return Produto<TipoA, Cte<TipoB>>(tipoA, tipoB);
  else
    return Produto<TipoA, TipoB>(tipoA, tipoB);
}

template <typename TipoA, typename TipoB>
auto operator % (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_integral_v<TipoA>)
    return Modulo<Cte<TipoA>, TipoB>(tipoA, tipoB);
  else if constexpr(is_integral_v<TipoB>)
    return Modulo<TipoA, Cte<TipoB>>(tipoA, tipoB);
  else
    return Modulo<TipoA, TipoB>(tipoA, tipoB);
}

template <typename TipoA, typename TipoB>
auto operator == (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_arithmetic_v<TipoA>)
    return Igual<Cte<TipoA>, TipoB>(tipoA, tipoB);
  else if constexpr(is_arithmetic_v<TipoB>)
    return Igual<TipoA, Cte<TipoB>>(tipoA, tipoB);
  else
    return Igual<TipoA, TipoB>(tipoA, tipoB);
}

template <typename TipoA, typename TipoB>
auto operator << (ostream& out, Soma<TipoA, TipoB> expressao) {
  return Imprime<Soma<TipoA, TipoB>>(out, expressao);
}

template <typename TipoA, typename TipoB>
auto operator << (ostream& out, Produto<TipoA, TipoB> expressao) {
  return Imprime<Produto<TipoA, TipoB>>(out, expressao);
}

template <typename TipoA, typename TipoB>
auto operator << (ostream& out, Modulo<TipoA, TipoB> expressao) {
  return Imprime<Modulo<TipoA, TipoB>>(out, expressao);
}

template <typename TipoA, typename TipoB>
auto operator << (ostream& out, Igual<TipoA, TipoB> expressao) {
  return Imprime<Igual<TipoA, TipoB>>(out, expressao);
}

auto operator << (ostream& out, X expressao) {
  return Imprime<X>(out, expressao);
}

template <typename Tipo>
Imprime<Tipo> operator << (Imprime<Tipo> imprime, const char& c) {
  imprime.add(c);
  return imprime;
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
      lambda(x);
    }
  }
}

X x;