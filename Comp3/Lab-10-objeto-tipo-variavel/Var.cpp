#include <iostream>
#include <string>
#include <type_traits>
#include <iterator>
#include <memory>
#include <map>

using namespace std;

class Undefined {
  public:
    virtual void imprime(ostream& out) const { out << "undefined"; };
    virtual Undefined getValor(const string& chave);
    virtual Undefined func(const int variavel);

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

    int value() const { return n; }
    void imprime(ostream& out) const { out << n; }
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

    void imprime(ostream& out) const { out << n; }
    double value() const { return n; }
};

class String: public Undefined {
  private:
    string n;
  public:
    String( string n ):n(n) {}

    void imprime(ostream& out) const { out << n; }
    string value() const { return n; }
};

class Object: public Undefined {
  private:
    map<string, Undefined> varByKey;
  
  public:
    Object(){};
    Object(map<string, Undefined> n): varByKey(n){};

    void imprime(ostream& out) const { 
      for (auto x : varByKey) {
        x.second.imprime(out);
      }
    }

    map<string, Undefined> value() {
      return varByKey;
    }
    
    Undefined getValor(const string& chave) {
      return varByKey[chave];
    }
};

Object newObject() {
  return Object();
}

class Var {
  private:
    shared_ptr<Undefined> valor;
  public:
    Var(): valor( new Undefined() ) {}
    Var(const int n): valor( new Int(n) ) {}
    Var(const double n): valor( new Double(n) ) {}
    Var(const string& n): valor( new String(n) ) {}
    template<int Tamanho>
    Var(const char (&n)[Tamanho]): valor( new String(string(n)) ) {}
    Var(Object n): valor( new Object(n.value()) ) {}

    class Erro {
      public:
        Erro( string msg ): msg(msg) {}
        
        string operator()() const {
          return msg;
        }
        
      private:
        string msg;
    };

    void imprime(ostream& out) const {
      valor->imprime(out);
    }

    Undefined operator [] (const string& chave) {
      return valor->getValor(chave);
    }

    template<int Tamanho>
    Undefined operator [] (const char (&chave)[Tamanho]) {
      return valor->getValor(string(chave));
    }

    Undefined operator () (int variavel) {
      return valor->func(variavel);
    }
};

Undefined Undefined::getValor(const string& chave) {
  throw Var::Erro("Essa variável não é um objeto");
}

Undefined Undefined::func(const int variavel) {
  throw Var::Erro("Essa variável não pode ser usada como função");

  return Undefined();
}

ostream& operator << (ostream& out , const Var& a ) { 
  a.imprime(out);

  return out;
}

ostream& operator << (ostream& out , const Undefined& a ) { 
  a.imprime(out);

  return out;
}
/* Var operator > ( const Var& a, const Var& b ) { return b<a; }
Var operator != ( const Var& a, const Var& b ) { return (a<b) || (b<a); }
Var operator == ( const Var& a, const Var& b ) { return !(a!=b); }
Var operator <= ( const Var& a, const Var& b ) { return !(b<a); }
Var operator >= ( const Var& a, const Var& b ) { return !(a<b); } */