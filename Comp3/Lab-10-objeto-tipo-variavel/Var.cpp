#include <iostream>
#include <memory>

using namespace std;

class Undefined {
};

class Int: public Undefined {
  private:
    int n;
  public:
    Int( int n ):n(n) {}
};

class Double: public Undefined {
  private:
    double n;
  public:
    Double( double n ):n(n) {}
};

class Var {
  private:
    shared_ptr<Undefined> valor;
  public:
    Var(): valor( new Undefined() ) {}
    
    Var operator = ( int n ) {
      valor = shared_ptr<Undefined>( new Int( n ) );
    }
    Var operator = ( double n ) {
      valor = shared_ptr<Undefined>( new Double( n ) );
    }
};

Var operator > ( const Var& a, const Var& b ) { return b<a; }
Var operator != ( const Var& a, const Var& b ) { return (a<b) || (b<a); }
Var operator == ( const Var& a, const Var& b ) { return !(a!=b); }
Var operator <= ( const Var& a, const Var& b ) { return !(b<a); }
Var operator >= ( const Var& a, const Var& b ) { return !(a<b); }