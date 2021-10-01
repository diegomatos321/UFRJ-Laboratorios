#include <iostream>
#include <string>
#include <type_traits>
#include <iterator>
#include <memory>
#include <map>

using namespace std;

class Var;

class Undefined {
  public:
    virtual void imprime(ostream& out) const { out << "undefined"; };
    virtual Undefined getValor(const string& chave);
    virtual Undefined func(const int variavel);

    virtual Var sel_soma( const shared_ptr<Undefined> arg1 ) const;
    virtual Var soma( int arg2 ) const;
    virtual Var soma( double arg2 ) const;
    virtual Var soma( char arg2 ) const;
    virtual Var soma( bool arg2 ) const;
    virtual Var soma( const string arg2 ) const;

    virtual Var sel_produto( const shared_ptr<Undefined> arg1 ) const;
    virtual Var produto( int arg2 ) const;
    virtual Var produto( double arg2 ) const;
    virtual Var produto( char arg2 ) const;
    virtual Var produto( bool arg2 ) const;
    virtual Var produto( const string arg2 ) const;

    virtual Var sel_divisao( const shared_ptr<Undefined> arg1 ) const;
    virtual Var divisao( int arg2 ) const;
    virtual Var divisao( double arg2 ) const;
    virtual Var divisao( char arg2 ) const;
    virtual Var divisao( bool arg2 ) const;
    virtual Var divisao( const string arg2 ) const;
};

class Int: public Undefined {
  private:
    int n;
  public:
    Int( int n ):n(n) {}

    int value() const { return n; }
    void imprime(ostream& out) const { out << n; }

    virtual Var sel_soma( const shared_ptr<Undefined> arg1 ) const;
    virtual Var soma( int arg2 ) const;
    virtual Var soma( double arg2 ) const;

    virtual Var sel_produto( const shared_ptr<Undefined> arg1 ) const;
    virtual Var produto( int arg2 ) const;
    virtual Var produto( double arg2 ) const;

    virtual Var sel_divisao( const shared_ptr<Undefined> arg1 ) const;
    virtual Var divisao( int arg2 ) const;
    virtual Var divisao( double arg2 ) const;
};

class Double: public Undefined {
  private:
    double n;
  public:
    Double( double n ):n(n) {}

    void imprime(ostream& out) const { out << n; }
    double value() const { return n; }

    virtual Var sel_soma( const shared_ptr<Undefined> arg1 ) const;
    virtual Var soma( int arg2 ) const;
    virtual Var soma( double arg2 ) const;

    virtual Var sel_produto( const shared_ptr<Undefined> arg1 ) const;
    virtual Var produto( int arg2 ) const;
    virtual Var produto( double arg2 ) const;

    virtual Var sel_divisao( const shared_ptr<Undefined> arg1 ) const;
    virtual Var divisao( int arg2 ) const;
    virtual Var divisao( double arg2 ) const;
};

class String: public Undefined {
  private:
    string n;
  public:
    String( string n ):n(n) {}

    void imprime(ostream& out) const { out << n; }
    string value() const { return n; }

    virtual Var sel_soma( const shared_ptr<Undefined> arg1 ) const;
    virtual Var soma( string& arg2 ) const;
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

    shared_ptr<Undefined> ptr() const {
      return valor;
    }

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

    Var operator + (const Var& arg1) const {
      return valor->sel_soma(arg1.ptr());
    }

    Var operator * (const Var& arg1) const {
      return valor->sel_produto(arg1.ptr());
    }

    Var operator / (const Var& arg1) const {
      return valor->sel_divisao(arg1.ptr());
    }
};

Undefined Undefined::getValor(const string& chave) {
  throw Var::Erro("Essa variável não é um objeto");
}

Undefined Undefined::func(const int variavel) {
  throw Var::Erro("Essa variável não pode ser usada como função");

  return Undefined();
}

Var Undefined::sel_soma( const shared_ptr<Undefined> arg1 ) const { return Var(); }
Var Undefined::soma( int arg2 ) const { return Var(); }
Var Undefined::soma( double arg2 ) const { return Var(); }
Var Undefined::soma( char arg2 ) const { return Var(); }
Var Undefined::soma( bool arg2 ) const { return Var(); }
Var Undefined::soma( const string arg2 ) const { return Var(); }  

Var Undefined::sel_produto( const shared_ptr<Undefined> arg1 ) const { return Var(); }
Var Undefined::produto( int arg2 ) const { return Var(); }
Var Undefined::produto( double arg2 ) const { return Var(); }
Var Undefined::produto( char arg2 ) const { return Var(); }
Var Undefined::produto( bool arg2 ) const { return Var(); }
Var Undefined::produto( const string arg2 ) const { return Var(); }  

Var Undefined::sel_divisao( const shared_ptr<Undefined> arg1 ) const { return Var(); }
Var Undefined::divisao( int arg2 ) const { return Var(); }
Var Undefined::divisao( double arg2 ) const { return Var(); }
Var Undefined::divisao( char arg2 ) const { return Var(); }
Var Undefined::divisao( bool arg2 ) const { return Var(); }
Var Undefined::divisao( const string arg2 ) const { return Var(); }  

Var Int::sel_soma( const shared_ptr<Undefined> arg1 ) const { arg1->soma( n ); }
Var Int::soma( int arg2 ) const { return Var(n + arg2); }
Var Int::soma( double arg2 ) const { return Var(n + arg2); }

Var Int::sel_produto( const shared_ptr<Undefined> arg1 ) const { arg1->produto( n ); }
Var Int::produto( int arg2 ) const { return Var(n * arg2); }
Var Int::produto( double arg2 ) const { return Var(n * arg2); }

Var Int::sel_divisao( const shared_ptr<Undefined> arg1 ) const { arg1->divisao( n ); }
Var Int::divisao( int arg2 ) const { return Var(n / arg2); }
Var Int::divisao( double arg2 ) const { return Var(n / arg2); }


Var Double::sel_soma( const shared_ptr<Undefined> arg1 ) const { arg1->soma( n ); }
Var Double::soma( int arg2 ) const { return Var(n + arg2); }
Var Double::soma( double arg2 ) const { return Var(n + arg2); }

Var Double::sel_produto( const shared_ptr<Undefined> arg1 ) const { arg1->produto( n ); }
Var Double::produto( int arg2 ) const { return Var(n * arg2); }
Var Double::produto( double arg2 ) const { return Var(n * arg2); }

Var Double::sel_produto( const shared_ptr<Undefined> arg1 ) const { arg1->produto( n ); }
Var Double::produto( int arg2 ) const { return Var(n / arg2); }
Var Double::produto( double arg2 ) const { return Var(n / arg2); }

ostream& operator << (ostream& out , const Var& a ) { 
  a.imprime(out);

  return out;
}

ostream& operator << (ostream& out , const Undefined& a ) { 
  a.imprime(out);

  return out;
}

Var operator > ( const Var& a, const Var& b ) { return b<a; }
Var operator != ( const Var& a, const Var& b ) { return (a<b) || (b<a); }
Var operator == ( const Var& a, const Var& b ) { return !(a!=b); }
Var operator <= ( const Var& a, const Var& b ) { return !(b<a); }
Var operator >= ( const Var& a, const Var& b ) { return !(a<b); }