#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <math.h>

using namespace std;

class X {
  public:
    double e(double generico) const {
      return generico;
    }

    double dx(double generico) const {
      return 1;
    }
};

class Cte {
  private:
    double valorConstante;
  
  public:
    Cte(double constante): valorConstante(constante) {}

    double e(double generico) const {
      return valorConstante;
    }

    double dx(double generico) const {
      return 0;
    }
};

template<typename TipoA, typename TipoB>
class Soma {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Soma(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    double e(double generico) const {
      return valorA.e(generico) + valorB.e(generico);
    }

    double dx(double generico) const {
      return valorA.dx(generico) + valorB.dx(generico);
    }
};

template<typename TipoA, typename TipoB>
class Subtracao {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Subtracao(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    double e(double generico) const {
      return valorA.e(generico) - valorB.e(generico);
    }

    double dx(double generico) const {
      return valorA.dx(generico) - valorB.dx(generico);
    }
};

template<typename TipoA, typename TipoB>
class Produto {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Produto(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    double e(double generico) const {
      return valorA.e(generico) * valorB.e(generico);
    }

    double dx(double generico) const {
      return (valorA.e(generico) * valorB.dx(generico)) + (valorA.dx(generico) * valorB.e(generico));
    }
};

template<typename TipoA, typename TipoB>
class Divisao {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Divisao(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    double e(double generico) const {
      return valorA.e(generico) / valorB.e(generico);
    }

    double dx(double generico) const {
      return ((valorA.e(generico) * valorB.dx(generico)) - (valorA.dx(generico) * valorB.e(generico))) / pow(valorB.e(generico), 2);
    }
};

template<typename Tipo>
class Seno {
  private:
    Tipo valor;
  
  public:
    Seno(Tipo tipo): valor(tipo) {}

    double e(double generico) const {
      return sin(valor.e(generico));
    }

    double dx(double generico) const {
      return cos(valor.e(generico)) * valor.dx(generico);
    }
};

template<typename Tipo>
class Cosseno {
  private:
    Tipo valor;
  
  public:
    Cosseno(Tipo tipo): valor(tipo) {}

    double e(double generico) const {
        return cos(valor.e(generico));
    }

    double dx(double generico) const {
        return -sin(valor.e(generico)) * valor.dx(generico);
    }
};

template<typename TipoA, typename TipoB>
auto operator + (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_integral_v<TipoA> || is_floating_point_v<TipoA>)
      return Soma<Cte, TipoB>(tipoA, tipoB);
  else if constexpr(is_integral_v<TipoB> || is_floating_point_v<TipoB>)
      return Soma<TipoA, Cte>( tipoA, tipoB );
  else
      return Soma<TipoA, TipoB>(tipoA, tipoB);
}

template<typename TipoA, typename TipoB>
auto operator - (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_integral_v<TipoA> || is_floating_point_v<TipoA>)
      return Subtracao<Cte, TipoB>(tipoA, tipoB);
  else if constexpr(is_integral_v<TipoB> || is_floating_point_v<TipoB>)
      return Subtracao<TipoA, Cte>( tipoA, tipoB );
  else
      return Subtracao<TipoA, TipoB>(tipoA, tipoB);
}

template<typename TipoA, typename TipoB>
auto operator * (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_integral_v<TipoA> || is_floating_point_v<TipoA>)
      return Produto<Cte, TipoB>(tipoA, tipoB);
  else if constexpr(is_integral_v<TipoB> || is_floating_point_v<TipoB>)
      return Produto<TipoA, Cte>( tipoA, tipoB );
  else
      return Produto<TipoA, TipoB>(tipoA, tipoB);
}

template<typename TipoA, typename TipoB>
auto operator / (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_integral_v<TipoA> || is_floating_point_v<TipoA>)
      return Divisao<Cte, TipoB>(tipoA, tipoB);
  else if constexpr(is_integral_v<TipoB> || is_floating_point_v<TipoB>)
      return Divisao<TipoA, Cte>( tipoA, tipoB );
  else
      return Divisao<TipoA, TipoB>(tipoA, tipoB);
}

template<typename Tipo>
Seno<Tipo> sin(Tipo x) {
  return Seno<Tipo>(x);
}

template<typename Tipo>
Cosseno<Tipo> cos(Tipo x) {
  return Cosseno<Tipo>(x);
}

X x;
