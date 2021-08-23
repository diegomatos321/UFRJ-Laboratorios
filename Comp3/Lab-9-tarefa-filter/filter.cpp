#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

template<int Tamanho, typename Functor>
void operator | (const int (&lista)[Tamanho], Functor lambda) {
  for (int i = 0; i < Tamanho; i++) {
    lambda(lista[i]);
  } 
}

template<typename Numero, typename Functor, typename = typename enable_if<is_arithmetic<Numero>::value>::type>
void operator | (const Numero& x, Functor lambda) {
  lambda(x);
}

template<typename Vector, typename Functor>
void operator | (const Vector& vetor, Functor lambda) {
  for (auto x : vetor) {
    lambda(x);
  } 
}

template<typename Functor>
void operator | (const string& str, Functor lambda) {
  for(const char& c : str) {
    lambda(c);
  }
}