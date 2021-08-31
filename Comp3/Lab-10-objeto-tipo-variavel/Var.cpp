#include <iostream>
#include <string>
#include <type_traits>
#include <iterator>
#include <memory>

using namespace std;

class Var;

class Undefined {
  public:
    virtual void imprime(ostream& out) {
      out << "Undefined";
    }

    virtual Undefined& getValor(string chave) {
      // throw new Var::Erro("Essa variável não é um objeto");
      cout << "Essa variável não é um objeto" << endl;

      return *this;
    }

/*     virtual Var sel_soma( Undefined* arg1 ) const { return Undefined(); }
    virtual Var soma( int arg2 ) const { return Undefined(); }
    virtual Var soma( double arg2 ) const { return Undefined(); }
    virtual Var soma( char arg2 ) const { return Undefined(); }
    virtual Var soma( bool arg2 ) const { return Undefined(); }
    virtual Var soma( string arg2 ) const { return Undefined(); }   */
};

class Int: public Undefined {
  private:
    int n;
  public:
    Int( int n ):n(n) {}

    int value() const {
      return n;
    }

    void imprime(ostream& out) {
      out << n;
    }
/* 
    virtual Var sel_soma( Undefined* arg1 ) const { arg1->soma( n ); }
    virtual Var soma( int arg2 ) const { return n + arg2; }
    virtual Var soma( double arg2 ) const { return n + arg2; } */
};

class Double: public Undefined {
  private:
    double n;
  public:
    Double( double n ):n(n) {}

    void imprime(ostream& out) {
      out << n;
    }
};

class String: public Undefined {
  private:
    string n;
  public:
    String( string n ):n(n) {}

    void imprime(ostream& out) {
      out << n;
    }
};

class Var {
  private:
    shared_ptr<Undefined> valor;
  public:
    class Erro {
      public:
        Erro( string msg ): msg(msg) {}
        
        string operator()() const {
          return msg;
        }
        
      private:
        string msg;
    };
    Var(): valor( new Undefined() ) {}
    // Var(const string& novaString): valor(new String(novaString)) {}

    template<typename Tipo>
    Var(const Tipo& novaVariavel) {
      if constexpr(is_same<string, Tipo>::value || is_same<char, decltype(novaVariavel[0])>::value) {
        valor = shared_ptr<Undefined>( new String( novaVariavel ) );
      }
      if constexpr(is_same<int, Tipo>::value) {
        valor = shared_ptr<Undefined>( new Int( novaVariavel ) );
      }
      if constexpr(is_same<double, Tipo>::value) {
        valor = shared_ptr<Undefined>( new Double( novaVariavel ) );
      }
    }

    Undefined& operator [] (string& chave) {
      return valor->getValor(chave);
    }

    void imprime(ostream& out) const {
      valor->imprime(out);
    }
};

ostream& operator << (ostream& out , const Var& a ) { 
  a.imprime(out);

  return out;
}
/* Var operator > ( const Var& a, const Var& b ) { return b<a; }
Var operator != ( const Var& a, const Var& b ) { return (a<b) || (b<a); }
Var operator == ( const Var& a, const Var& b ) { return !(a!=b); }
Var operator <= ( const Var& a, const Var& b ) { return !(b<a); }
Var operator >= ( const Var& a, const Var& b ) { return !(a<b); } */