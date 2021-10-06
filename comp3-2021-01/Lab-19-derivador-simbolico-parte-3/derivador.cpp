#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <math.h>
#include <iomanip>
#include <sstream>

using namespace std;

string excecaoSoma(string esquerda, string direita);
string excecaoSubtracao(string esquerda, string direita);
string excecaoProduto(string esquerda, string direita);
string excecaoPotencia(string esquerda, string direita);

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

      result = excecaoSoma(esquerda, direita);

      return result;
    }
    
    string dx_str() const {
      return excecaoSoma(valorA.dx_str(), valorB.dx_str());
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

      result = excecaoSubtracao(esquerda, direita);

      return result;
    }
    
    string dx_str() const {
      return excecaoSubtracao(valorA.dx_str(), valorB.dx_str());
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
      direita = (precedencia() > valorB.precedencia() ? "(" + valorB.str() + ")" : valorB.str());

      result = excecaoProduto(esquerda, direita);
      
      return result;
    }
    
    string dx_str() const {
      string esquerda, direita, str_valorA, str_valorB, dx_valorA, dx_valorB, result;

      esquerda = excecaoProduto(valorA.dx_str(), valorB.str());
      direita = excecaoProduto(valorA.str(), valorB.dx_str());
      
      result = excecaoSoma(esquerda, direita);

      return result;
    }
};

template<typename TipoA, typename TipoB>
class Divisao {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Divisao(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    const int precedencia() const {
      return 2;
    }

    double e(double generico) const {
      return valorA.e(generico) / valorB.e(generico);
    }

    double dx(double generico) const {
      return ((valorA.e(generico) * valorB.dx(generico)) - (valorA.dx(generico) * valorB.e(generico))) / pow(valorB.e(generico), 2);
    }

    string str() const {
      string esquerda, direita, result;

      esquerda = (precedencia() > valorA.precedencia() ? "(" + valorA.str() + ")" : valorA.str());
      direita = (precedencia() >= valorB.precedencia() ? "(" + valorB.str() + ")" : valorB.str());

      result = esquerda + "/" + direita;

      return result;

      // return "((" + valorA.str() + ")/(" + valorB.str() + "))";
    }
    
    string dx_str() const {
      string valorA_str, valorB_str, esquerda, meio, direita, result;

      valorA_str = (precedencia() > valorA.precedencia() ? "(" + valorA.str() + ")" : valorA.str());
      valorB_str = (precedencia() >= valorB.precedencia() ? "(" + valorB.str() + ")" : valorB.str());

      esquerda = excecaoProduto(valorA.dx_str(), valorB_str);
      meio = excecaoProduto(valorA_str, valorB.dx_str());
      direita = excecaoPotencia(valorB_str, "2");

      esquerda = excecaoSubtracao(esquerda, meio);
      result = esquerda + "/" + direita;

      return result;

      // return "((((" + valorA.dx_str() + ")*(" + valorB.str() + "))-((" + valorA.str() + ")*(" + valorB.dx_str() + ")))/((" + valorB.str() + "^2)))";
    }
};

template<typename TipoA, typename TipoB>
class Potencia {
  private:
    TipoA valorA;
    TipoB valorB;
  
  public:
    Potencia(TipoA tipoA, TipoB tipoB): valorA(tipoA), valorB(tipoB) {}

    const int precedencia() const {
      return 3;
    }

    double e(double generico) const {
      return pow(valorA.e(generico), valorB.e(generico));
    }

    double dx(double generico) const {
      return valorB.e(generico) * pow(valorA.e(generico), valorB.e(generico) - 1) * valorA.dx(generico);
    }

    string str() const {
      string esquerda, direita, result;

      esquerda = (precedencia() > valorA.precedencia() ? "(" + valorA.str() + ")" : valorA.str());
      direita = (precedencia() > valorB.precedencia() ? "(" + valorB.str() + ")" : valorB.str());

      result = excecaoPotencia(esquerda, direita);

      return result;
      // return "(" + valorA.str() + ")^" + valorB.str();
    }
    
    string dx_str() const {
      string esquerda, direita, str_valorA, str_valorB, result;

      auto tempSub = Subtracao<TipoB, Cte>(valorB, 1);
      stringstream streamSubtraction;
      streamSubtraction << fixed << setprecision(0) << tempSub.e(1);

      str_valorA = (precedencia() > valorA.precedencia() ? "(" + valorA.str() + ")" : valorA.str());
      str_valorB = (precedencia() > valorB.precedencia() ? "(" + valorB.str() + ")" : valorB.str());

      esquerda = excecaoProduto(str_valorB, valorA.dx_str());
      direita = excecaoPotencia(str_valorA, streamSubtraction.str());

      result = excecaoProduto(esquerda, direita);

      return result;

      // return "(" + valorB.str() + "*(" + valorA.dx_str() + ")*(" + valorA.str() + ")^" + streamSubtraction.str() + ")";
    }
};

template<typename Tipo>
class Seno {
  private:
    Tipo valor;
  
  public:
    Seno(Tipo tipo): valor(tipo) {}

    const int precedencia() const {
      return 3;
    }

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
      string esquerda, result;
      
      esquerda = "cos(" + valor.str() + ")";

      result = excecaoProduto(esquerda, valor.dx_str());

      return result;
    }
};

template<typename Tipo>
class Cosseno {
  private:
    Tipo valor;
  
  public:
    Cosseno(Tipo tipo): valor(tipo) {}

    const int precedencia() const {
      return 3;
    }

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
      string esquerda, result;

      esquerda = "-sin(" + valor.str() + ")";

      result = excecaoProduto(esquerda, valor.dx_str());

      return result;
    }
};

template<typename Tipo>
class Exponencial {
  private:
    Tipo valor;
  
  public:
    Exponencial(Tipo tipo): valor(tipo) {}

    const int precedencia() const {
      return 3;
    }

    double e(double generico) const {
      return exp(valor.e(generico));
    }

    double dx(double generico) const {
      return exp(valor.e(generico)) * valor.dx(generico);
    }

    string str() const {
      string result;

      result = (precedencia() > valor.precedencia() ? "(" + valor.str() + ")" : valor.str());

      return "exp" + result;
    }

    string dx_str() const {
      string esquerda, direita, result;

      esquerda = "exp(" + valor.str() + ")";
      direita = "(" + valor.dx_str() + ")";

      result = excecaoProduto(esquerda, direita);

      return result;
    }
};

template<typename Tipo>
class Logaritmo {
  private:
    Tipo valor;
  
  public:
    Logaritmo(Tipo tipo): valor(tipo) {}

    const int precedencia() const {
      return 3;
    }

    double e(double generico) const {
        return log(valor.e(generico));
    }

    double dx(double generico) const {
        return 1/valor.e(generico) * valor.dx(generico);
    }

    string str() const {
      string str_valor, result;

      str_valor = (precedencia() > valor.precedencia() ? "(" + valor.str() + ")" : valor.str());

      result = "log" + str_valor + "";

      return result;
    }

    string dx_str() const {
      string esquerda, result;

      esquerda = (precedencia() > valor.precedencia() ? "(" + valor.str() + ")" : valor.str());

      result = excecaoProduto(esquerda, valor.dx_str());

      return "1/" + result;
      // return "1/(" + valor.str() + ")*(" + valor.dx_str() + ")";
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

string excecaoSoma(string esquerda, string direita) {
  string result = "";

  if(esquerda == "0" || esquerda == "(0)") 
    result = direita;
  else if(direita == "0" || direita == "(0)")
    result = esquerda;
  else
    result = esquerda + "+" + direita;

  return result;
}

string excecaoSubtracao(string esquerda, string direita) {
  string result = "";

  if(esquerda == "0" || esquerda == "(0)") 
    result = "-" + direita;
  else if(direita == "0" || direita == "(0)")
    result = esquerda;
  else
    result = esquerda + "-" + direita;

  return result;
}

string excecaoProduto(string esquerda, string direita) {
  string result = "";

  if(esquerda == "1" || esquerda == "(1)")
    result = direita;
  else if(direita == "1" || direita == "(1)")
    result = esquerda;
  else if(esquerda == "0" || direita == "0" || esquerda == "(0)" || direita == "(0)")
    result = "0";
  else
    result = esquerda + "*" + direita;

  return result;
}

string excecaoPotencia(string esquerda, string direita) {
  string result = "";

  if(direita == "0" || direita == "(0)")
    result = "1";
  else if((direita == "1" && esquerda != "x") || (direita == "1" && esquerda != "(x)") ||
          (direita == "(1)" && esquerda != "(x)") || (direita == "(1)" && esquerda != "x"))
    result = esquerda;
  else if((direita == "1" && esquerda == "x") || (direita == "1" && esquerda == "(x)") ||
          (direita == "(1)" && esquerda == "(x)") || (direita == "(1)" && esquerda == "x"))
    result = esquerda;
  else if(esquerda == "x" || esquerda == "(x)")
    result = esquerda + "^" + direita;
  else
    result = esquerda + "^" + direita;

  return result;
}

X x;