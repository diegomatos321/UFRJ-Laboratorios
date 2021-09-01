#include <iostream>
#include <string>
#include <type_traits>
#include <iterator>
#include <memory>

using namespace std;

class Var;

class Undefined {
  public:
    virtual void imprime(ostream& out) const {
      out << "undefined";
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

    void imprime(ostream& out) const {
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

    void imprime(ostream& out) const {
      out << n;
    }

    double value() const {
      return n;
    }
};

class String: public Undefined {
  private:
    string n;
  public:
    String( string n ):n(n) {}
    template<int Tamanho>
    String( const char (&n)[Tamanho] ):n(n) {}
    
    void imprime(ostream& out) const {
      out << n;
    }

    string value() const {
      return n;
    }
};

class Var {
  private:
    shared_ptr<Undefined> valor;
  public:
    Var(): valor( new Undefined() ) {}
    Var(const int n): valor( new Int(n) ) {}
    Var(const double n): valor( new Double(n) ) {}
    Var(const string n): valor( new String(n) ) {}
    template<int Tamanho>
    Var(const char (&n)[Tamanho]): valor( new String(n) ) {}

    class Erro {
      public:
        Erro( string msg ): msg(msg) {}
        
        string operator()() const {
          return msg;
        }
        
      private:
        string msg;
    };

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