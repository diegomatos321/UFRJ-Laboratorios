#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <math.h>
#include <iomanip>
#include <sstream>

using namespace std;

class X {
  public:
    const int precedencia() const {
      return 4;
    }

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

    const int precedencia() const {
      return 4;
    }

    double e(double generico) const {
      return valorConstante;
    }

    double dx(double generico) const {
      return 0;
    }

    string str() const {
      stringstream stream;
      double parteInteira = 0;

      if (modf(valorConstante, &parteInteira) == 0) {
        stream << fixed << setprecision(0) << parteInteira;
      }
      else {
        stream << valorConstante << setprecision(2);
      }

      return stream.str();
    }
    
    string dx_str() const {
      return "0";
    }
};

template<typename TipoA, typename TipoB>
class Soma {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Soma(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    const int precedencia() const {
      return 1;
    }

    double e(double generico) const {
      return valorA.e(generico) + valorB.e(generico);
    }

    double dx(double generico) const {
      return valorA.dx(generico) + valorB.dx(generico);
    }
    
    string str() const {
      string esquerda, direita, result;

      esquerda = (precedencia() > valorA.precedencia() ? "(" + valorA.str() + ")" : valorA.str());
      direita = (precedencia() >= valorB.precedencia() ? "(" + valorB.str() + ")" : valorB.str());

      // Todo: Criar Função Excecao Soma
      if(esquerda == "0")
        result = direita;
      else if(direita == "0")
        result = esquerda;
      else
        result = esquerda + "+" + direita;

      return result;
    }
    
    string dx_str() const {
      string esquerda, direita, result;

      esquerda = (precedencia() > valorA.precedencia() ? "(" + valorA.dx_str() + ")" : valorA.dx_str());
      direita = (precedencia() >= valorB.precedencia() ? "(" + valorB.dx_str() + ")" : valorB.dx_str());

      // Todo: Criar Função Excecao Soma
      if(esquerda == "0")
        result = direita;
      else if(direita == "0")
        result = esquerda;
      else
        result = esquerda + "+" + direita;

      return result;
    }
};

template<typename TipoA, typename TipoB>
class Subtracao {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Subtracao(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    const int precedencia() const {
      return 1;
    }

    double e(double generico) const {
      return valorA.e(generico) - valorB.e(generico);
    }

    double dx(double generico) const {
      return valorA.dx(generico) - valorB.dx(generico);
    }

    string str() const {
      string esquerda, direita, result;

      esquerda = (precedencia() > valorA.precedencia() ? "(" + valorA.str() + ")" : valorA.str());
      direita = (precedencia() >= valorB.precedencia() ? "(" + valorB.str() + ")" : valorB.str());
      
      // Todo: Criar Função Excecao Subtracao
      if(esquerda == "0")
        result = direita;
      else if(direita == "0")
        result = esquerda;
      else
        result = esquerda + "-" + direita;
      
      return result;
    }
    
    string dx_str() const {
      string esquerda, direita, result;

      esquerda = (precedencia() > valorA.precedencia() ? "(" + valorA.dx_str() + ")" : valorA.dx_str());
      direita = (precedencia() >= valorB.precedencia() ? "(" + valorB.dx_str() + ")" : valorB.dx_str());

      if(esquerda == "0")
        result = direita;
      else if(direita == "0")
        result = esquerda;
      else
        result = esquerda + "-" + direita;

      return result;
    }
};

template<typename TipoA, typename TipoB>
class Produto {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Produto(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    const int precedencia() const {
      return 2;
    }

    double e(double generico) const {
      return valorA.e(generico) * valorB.e(generico);
    }

    double dx(double generico) const {
      return (valorA.e(generico) * valorB.dx(generico)) + (valorA.dx(generico) * valorB.e(generico));
    }

    string str() const {
      string esquerda, direita, result;

      esquerda = (precedencia() > valorA.precedencia() ? "(" + valorA.str() + ")" : valorA.str());
      direita = (precedencia() >= valorB.precedencia() ? "(" + valorB.str() + ")" : valorB.str());

      // TODO: Transformar em função = Excecao Produto
      if(esquerda == "1")
        result = direita;
      else if(direita == "1")
        result = esquerda;
      else if(esquerda == "0" || direita == "0")
        result = "0";
      else
        result = esquerda + "*" + direita;
      
      return result;
    }
    
    string dx_str() const {
      string esquerda, direita, str_valorA, str_valorB, dx_valorA, dx_valorB, result;

      str_valorA = (precedencia() > valorA.precedencia() ? "(" + valorA.str() + ")" : valorA.str());
      str_valorB = (precedencia() >= valorB.precedencia() ? "(" + valorB.str() + ")" : valorB.str());

      dx_valorA = (precedencia() > valorA.precedencia() ? "(" + valorA.dx_str() + ")" : valorA.dx_str());
      dx_valorB = (precedencia() >= valorB.precedencia() ? "(" + valorB.dx_str() + ")" : valorB.dx_str());

      if(dx_valorA == "1")
        esquerda = str_valorB;
      else if(str_valorB == "1")
        esquerda = dx_valorA;
      else if(dx_valorA == "0" || str_valorB == "0")
        esquerda = "0";
      else
        esquerda = "(" + dx_valorA + "*" + str_valorB + ")";
      
      if(str_valorA == "1")
        direita = dx_valorB;
      else if(dx_valorB == "1")
        direita = str_valorA;
      else if(str_valorA == "0" || dx_valorB == "0")
        direita = "0";
      else
        direita = "(" + str_valorA + "*" + dx_valorB + ")";

      if(esquerda == "1" || esquerda == "0")
        esquerda = "";
      if(direita == "1" || direita == "0")
        direita = "";
      
      if(esquerda == "" && direita != "")
        result = direita;
      else if(esquerda != "" && direita == "")
        result = esquerda;
      else if(esquerda == "" && direita == "")
        result = "";
      else
        result = esquerda + "+" + direita;

      return result;
      
      // return "(((" + valorA.dx_str() + ")*(" + valorB.str() + "))+((" + valorA.str() + ")*(" + valorB.dx_str() + ")))";
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
      return "((" + valorA.str() + ")/(" + valorB.str() + "))";
    }
    
    string dx_str() const {
      return "((((" + valorA.dx_str() + ")*(" + valorB.str() + "))-((" + valorA.str() + ")*(" + valorB.dx_str() + ")))/((" + valorB.str() + "^2)))";
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
      return "(" + valorA.str() + ")^" + valorB.str();
    }
    
    string dx_str() const {
      auto tempSub = Subtracao<TipoB, Cte>(valorB, 1);
      stringstream streamSubtraction;
      streamSubtraction << fixed << setprecision(0) << tempSub.e(1);

      return "(" + valorB.str() + "*(" + valorA.dx_str() + ")*(" + valorA.str() + ")^" + streamSubtraction.str() + ")";
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

    string str() const {
      return "sin(" + valor.str() + ")";
    }

    string dx_str() const {
      return "cos(" + valor.str() + ")*(" + valor.dx_str() + ")";
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

    string str() const {
      return "cos(" + valor.str() + ")";
    }

    string dx_str() const {
      return "-sin(" + valor.str() + ")*(" + valor.dx_str() + ")";
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

    string str() const {
      return "exp(" + valor.str() + ")";
    }

    string dx_str() const {
      return "(exp(" + valor.str() + ")*(" + valor.dx_str() + "))";
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

    string str() const {
      return "log((" + valor.str() + "))";
    }

    string dx_str() const {
      return "1/(" + valor.str() + ")*(" + valor.dx_str() + ")";
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