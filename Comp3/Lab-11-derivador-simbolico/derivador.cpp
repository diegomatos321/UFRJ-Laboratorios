#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

using namespace std;

class Expressao {
  private:
    vector<string> expressao;

  public:
    template<typename Tipo>
    void push(Tipo& valor) {
      if constexpr(is_same<Tipo, string>::value) {
        expressao.push_back(valor);
      }
      else if constexpr(is_arithmetic<Tipo>::value) {
        expressao.push_back(to_string(valor));
      }
    }

    void print(ostream& out) {
      for (string x: expressao) {
        out << x;
      }
    }

    template<typename Tipo>
    Tipo e(Tipo& x){
      return x;
    }

    template<typename Tipo>
    Tipo dx(Tipo& x){
      return x;
    }
};

class X {
  public:
    template<typename Tipo>
    Expressao operator * (Tipo& n) {
      if constexpr(is_same<Tipo, Expressao>::value) {
        n.push("*");
        n.push("x");

        return n;
      }
      else {
        Expressao expressao;
        
        expressao.push(n);
        expressao.push("*");
        expressao.push("x");
        
        return expressao;
      }
    }
};
