#include <iostream>
#include <string>
#include <type_traits>
#include <iterator>
#include <memory>

using namespace std;

class Undefined {
  public:
    virtual void imprime(ostream& out) const;
    virtual Undefined getValor(const string& chave);
/*     template<int Tamanho>
    virtual Undefined& getValor(const char (&frase)[Tamanho]) {
      cout << "Essa variável não é um objeto" << endl;

      return *this;
    } */

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

    int value() const;
    void imprime(ostream& out) const;
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

    void imprime(ostream& out) const;
    double value() const;
};

class String: public Undefined {
  private:
    string n;
  public:
    String( string n ):n(n) {}

    void imprime(ostream& out) const;
    string value() const;
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
    Var(const char (&n)[Tamanho]): valor( new String(string(n)) ) {}

    class Erro {
      public:
        Erro( string msg ): msg(msg) {}
        
        string operator()() const {
          return msg;
        }
        
      private:
        string msg;
    };

    void imprime(ostream& out) const;
    Undefined operator [] (const string& chave);
    template<int Tamanho>
    Undefined operator [] (const char (&chave)[Tamanho]);
};

void Undefined::imprime(ostream& out) const { out << "undefined"; };
Undefined Undefined::getValor(const string& chave) {
  throw Var::Erro("Essa variável não é um objeto");
  return Undefined();
}

int Int::value() const { return n; }
void Int::imprime(ostream& out) const { out << n; }

void Double::imprime(ostream& out) const { out << n; }
double Double::value() const { return n; }

void String::imprime(ostream& out) const { out << n; }
string String::value() const { return n; }

void Var::imprime(ostream& out) const {
  valor->imprime(out);
}

Undefined Var::operator [] (const string& chave) {
  return valor->getValor(chave);
}

template<int Tamanho>
Undefined Var::operator [] (const char (&chave)[Tamanho]) {
  return valor->getValor(string(chave));
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