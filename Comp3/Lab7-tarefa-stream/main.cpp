#include <iostream>
#include <vector>

using namespace std;

void print( int x ) { cout << x << " "; }

template<typename Functor>
void operator | (int lista[], Functor lambda) {
  for (auto i = begin(*lista); i != end(*lista); ++i) {
    lambda(*i);
  }
}

/* template<typename Lista, typename Functor>
void operator | (Lista lista, Functor lambda) {
  for (auto x: lista)
  {
    lambda(x);
  }
} */

int main() {
  int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
  // vector<int> v{ 2 , 6, 8 };

  // tab | []( int x ) { cout << x*x << endl; };
  // tab | [ &v ]( int x ) { v.push_back( x ); };
  // v | []( int x ) { cout << x*x << endl; };
  // v | &print;

  return 0;
}