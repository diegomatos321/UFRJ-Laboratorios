#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>

#include "apply.cpp"

using namespace std;

void teste3();
// void teste5();
void teste8();
void teste9();

double seno(double n) { return sin(n); }

int id(int n) { return n; }

int sqr(int a) { return a * a; }

string roman(int n)
{
  map<int, string> rom = {{1, "I"}, {2, "II"}, {3, "III"}, {4, "IV"}, {5, "V"}, {6, "VI"}, {7, "VII"}, {8, "VIII"}};

  return rom[n];
}

struct FunctorSimples
{
  string operator()(int n) { return roman(n) + "!"; }
};

struct FunctorTemplate
{
  template <typename T>
  T operator()(T n) { return n + n; }
};

template <typename T>
ostream &operator<<(ostream &o, const vector<T> &v)
{
  o << "[ ";
  for (auto x : v)
    o << x << " ";

  return o << "]";
}

int main(int argc, char *argv[]) {
  // teste3();
  // teste5();
  // teste8();
  teste9();

  return 0;
}

void teste3() {
  auto v = { 1, 2, 3, 4, 5 };
  cout << ::apply( v, []( auto n ) -> double { return n*n + 0.1; } );
}

/* void teste5() {
  auto a = { 1, 2 }, b = { 3, 4 };
  cout << ::apply( a, [b]( auto x ) { return ::apply( b, [x]( auto y ){ return vector{ x, y }; } ); } );
}
 */

void teste8() {
  cout << ::apply( { 1, 2, 3, 4, 5 }, roman );
}

void teste9() {
  int v[] = { 1, 2, 3, 4, 5 };
  vector<int> r = ::apply( v, id );
  cout << r;
}