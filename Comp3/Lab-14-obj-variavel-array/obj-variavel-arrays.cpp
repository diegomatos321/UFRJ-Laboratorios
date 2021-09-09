#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include <memory>
#include <variant>
#include <functional>

using namespace std;

class Var {
  public:
    class Erro {
      private:
        string msg;

      public:
        Erro( string msg ): msg(msg) {}
        
        string operator()() const {
          return msg;
        }
    };
  
  private:
    class Undefined {};

    class Object {
      private:
        map<string, Var> atr;

      public:
        virtual ~Object() {}
        
        virtual void print( ostream& o ) const { 
          o << "object";
        }
        
        virtual Var invoke( const Var& arg ) const { 
          throw Erro( "Essa variável não pode ser usada como função" ); 
        }  
        
        Var& lvalue( const string& st ) { return atr[st]; }
        Var rvalue( const string& st ) const { 
          if( auto x = atr.find( st ); x != atr.end() )
            return x->second;
          else
            return Var(); 
        }
    };

    template <typename F>
    class Function: public Object {
      private:
        F f;

      public:
        Function( F f ): f(f) {}

        virtual void print( ostream& o ) const { 
          o << "function"; 
        }
        
        virtual Var invoke( const Var& arg ) const { 
          return invoke( f, arg ); 
        }  
      };

    enum { UNDEFINED, BOOL, CHAR, INT, DOUBLE, STRING, OBJECT };

    typedef variant<Undefined, bool, char, int, double, string, shared_ptr<Object>> Variant;
    Variant v;
  
  public:
    Var(): v() {}
    Var( const char* st ): v( string(st) ) {}
    Var( bool v ): v(v) {}
    Var( char v ): v(v) {}
    Var( int v ): v(v) {}
    Var( double v ): v(v) {}
    Var( string v ): v(v) {}
    Var( Object* v ): v( shared_ptr<Object>( v ) ) {}
    
    template <typename T>
    Var( T func ): v( shared_ptr<Object>( new Function<T>( func ) ) ) {}
    
    Var operator()( Var arg ) const {
      if( v.index() != OBJECT )
        throw Erro( "Essa variável não pode ser usada como função" );
        
      return get<OBJECT>( v )->invoke( arg );
    }
    
    void print( ostream& o ) const {
      switch( v.index() ) {
        case UNDEFINED	: o << "undefined"; break;
        case BOOL		: o << (get<BOOL>( v ) ? "true" : "false"); break;
        case CHAR		: o << get<CHAR>( v ); break;
        case INT		: o << get<INT>( v ); break;
        case DOUBLE	: o << get<DOUBLE>( v ); break;
        case STRING 	: o << get<STRING>( v ); break;
        case OBJECT	: get<OBJECT>( v )->print( o ); break;
      
        default:
          throw Erro( "Tipo indefinido (bug)" );
      }
    }
    
    static constexpr int tipo( int a, int b ) { return (a << 4) | b; }
    
    static Var sel_soma( const Var& a, const Var& b ) {
      switch( tipo( a.v.index(), b.v.index() ) ) {
        case tipo( INT, INT ): return get<INT>( a.v ) + get<INT>( b.v );
        case tipo( DOUBLE, DOUBLE ): return get<DOUBLE>( a.v ) + get<DOUBLE>( b.v );
        case tipo( DOUBLE, INT ): return get<DOUBLE>( a.v ) + get<INT>( b.v );
        case tipo( INT, DOUBLE ): return get<INT>( a.v ) + get<DOUBLE>( b.v );

        case tipo( CHAR, CHAR ): return string("") + get<CHAR>( a.v ) + get<CHAR>( b.v );
        case tipo( STRING, STRING ): return get<STRING>( a.v ) + get<STRING>( b.v );
        case tipo( STRING, CHAR ): return get<STRING>( a.v ) + get<CHAR>( b.v );
        case tipo( CHAR, STRING ): return get<CHAR>( a.v ) + get<STRING>( b.v );
        
        default:
          return Var();
      }
    }
};

ostream& operator << ( ostream& o, const Var& v ) {
  v.print( o );
  return o;
}

inline Var operator + ( const Var& a, const Var& b ) {
  return Var::sel_soma( a, b );
}