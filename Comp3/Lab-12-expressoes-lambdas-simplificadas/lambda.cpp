#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

template<typename Tipo>
Tipo getTipo(Tipo tipo) {
  return tipo;
}

template<typename Iteravel, typename Functor>
auto operator | (const Iteravel& iteravel, Functor lambda) {
  if constexpr(is_same<decltype(lambda(*begin(iteravel))), bool>::value) {
    vector<decltype(getTipo(*begin(iteravel)))> tempVetor;

    for (auto x : iteravel) {
      if (lambda(x)) {
        tempVetor.push_back(x);
      }
    }

    return tempVetor;
  }
  else if constexpr(is_same<decltype(lambda(*begin(iteravel))), void>::value == false) {
    vector<decltype(lambda(*begin(iteravel)))> tempVetor;

    for (auto x : iteravel) {
      tempVetor.push_back(lambda(x));
    }

    return tempVetor;
  }
  else {
    for (auto x : iteravel) {
      lambda(x);
    }
  }
}