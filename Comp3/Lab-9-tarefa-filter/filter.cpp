#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

using namespace std;

template<int Tamanho, typename Functor>
auto operator | (const int (&lista)[Tamanho], Functor lambda) {
  if constexpr(is_same<decltype(lambda(lista[0])), bool>::value) {
    vector<int> tempVetor;

    for (int i = 0; i < Tamanho; i++) {
      if (lambda(lista[i]) == true) {
        tempVetor.push_back(lista[i]);
      }
    }

    return tempVetor;
  }
  else {
    for (int i = 0; i < Tamanho; i++) {
      lambda(lista[i]);
    } 
  }
}

template<typename Numero, typename Functor, typename = typename enable_if<is_arithmetic<Numero>::value>::type>
void operator | (const Numero& x, Functor lambda) {
  lambda(x);
}

template<typename Vector, typename Functor>
auto operator | (const Vector& vetor, const Functor lambda) {
  if constexpr(is_same<decltype(lambda(vetor[0])), bool>::value) {
    Vector tempVetor;
    for (auto x : vetor) {
      if (lambda(x)) {
        tempVetor.push_back(x);
      }
    } 

    return tempVetor;
  }
  else {
    for (auto x : vetor) {
      lambda(x);
    }
  }
}

template<typename Functor>
void operator | (const string& str, Functor lambda) {
  for(const char& c : str) {
    lambda(c);
  }
}