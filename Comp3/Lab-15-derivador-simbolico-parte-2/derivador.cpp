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

    string str() const {
      return "x";
    }
    
    string dx_str() const {
      return "1";
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

    string str() const {
      return "(" + to_string(valorConstante) + ")";
    }
    
    string dx_str() const {
      return "(0)";
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
    
    string str() const {
      return "(" + valorA.str() + ")+(" + valorB.str() + ")";
    }
    
    string dx_str() const {
      return "(" + valorA.dx_str() + ")+(" + valorB.dx_str() + ")";
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

    string str() const {
      return "(" + valorA.str() + ")-(" + valorB.str() + ")";
    }
    
    string dx_str() const {
      return "(" + valorA.dx_str() + ")-(" + valorB.dx_str() + ")";
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

    string str() const {
      return "(" + valorA.str() + ")*(" + valorB.dx_str() + ")+(" + (valorA.dx_str() + ")*(" + valorB.str() + ")";
    }
    
    string dx_str() const {
      return "(" + valorA.dx_str() + ")*(" + valorB.dx_str() + ")";
    }
};

template<typename TipoA, typename TipoB>
class Potencia {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Potencia(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    double e(double generico) const {
      return pow(valorA.e(generico), valorB.e(generico));
    }

    double dx(double generico) const {
      return valorB.e(generico) * pow(valorA.e(generico), valorB.e(generico) - 1) * valorA.dx(generico);
    }

    string str() const {
      return "(" + valorA.str() + ")^(" + valorB.str() + ")";
    }
    
    string dx_str() const {
      return "(" + valorA.dx_str() + ")^(" + valorB.dx_str() + ")";
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

    string str() const {
      return "(" + valorA.str() + ")/(" + valorB.str() + ")";
    }
    
    string dx_str() const {
      return "(" + valorA.dx_str() + ")/(" + valorB.dx_str() + ")";
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

template<typename Tipo>
class Exponencial {
  private:
    Tipo valor;
  
  public:
    Exponencial(Tipo tipo): valor(tipo) {}

    double e(double generico) const {
        return exp(valor.e(generico));
    }

    double dx(double generico) const {
        return exp(valor.e(generico)) * valor.dx(generico);
    }
};

template<typename Tipo>
class Logaritmo {
  private:
    Tipo valor;
  
  public:
    Logaritmo(Tipo tipo): valor(tipo) {}

    double e(double generico) const {
        return log(valor.e(generico));
    }

    double dx(double generico) const {
        return 1/valor.e(generico) * valor.dx(generico);
    }
};

template<typename TipoA, typename TipoB>
auto operator + (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_arithmetic_v<TipoA>)
      return Soma<Cte, TipoB>(tipoA, tipoB);
  else if constexpr(is_arithmetic_v<TipoB>)
      return Soma<TipoA, Cte>( tipoA, tipoB );
  else
      return Soma<TipoA, TipoB>(tipoA, tipoB);
}

template<typename TipoA, typename TipoB>
auto operator - (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_arithmetic_v<TipoA>)
      return Subtracao<Cte, TipoB>(tipoA, tipoB);
  else if constexpr(is_arithmetic_v<TipoB>)
      return Subtracao<TipoA, Cte>( tipoA, tipoB );
  else
      return Subtracao<TipoA, TipoB>(tipoA, tipoB);
}

template<typename TipoA, typename TipoB>
auto operator * (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_arithmetic_v<TipoA>)
      return Produto<Cte, TipoB>(tipoA, tipoB);
  else if constexpr(is_arithmetic_v<TipoB>)
      return Produto<TipoA, Cte>( tipoA, tipoB );
  else
      return Produto<TipoA, TipoB>(tipoA, tipoB);
}

template<typename TipoA, typename TipoB>
auto operator / (TipoA tipoA, TipoB tipoB) {
  if constexpr(is_arithmetic_v<TipoA>)
      return Divisao<Cte, TipoB>(tipoA, tipoB);
  else if constexpr(is_arithmetic_v<TipoB>)
      return Divisao<TipoA, Cte>( tipoA, tipoB );
  else
      return Divisao<TipoA, TipoB>(tipoA, tipoB);
}

template<typename TipoA, typename TipoB>
Potencia<TipoA, Cte> operator ->* (TipoA tipoA, TipoB tipoB) {
  static_assert(!is_same_v<double, TipoB>, "Operador de potenciação definido apenas para inteiros");

  return Potencia<TipoA, Cte>(tipoA, tipoB);
}

template<typename Tipo>
Seno<Tipo> sin(Tipo x) {
  return Seno<Tipo>(x);
}

template<typename Tipo>
Cosseno<Tipo> cos(Tipo x) {
  return Cosseno<Tipo>(x);
}

template<typename Tipo>
Exponencial<Tipo> exp(Tipo x) {
  return Exponencial<Tipo>(x);
}

template<typename Tipo>
Logaritmo<Tipo> log(Tipo x) {
  return Logaritmo<Tipo>(x);
}

X x;