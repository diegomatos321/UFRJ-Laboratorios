#include <iostream>
#include <type_traits>
#include <vector>
#include <iterator>
#include <functional>

using namespace std;

template<typename Iteravel, typename Functor>
auto operator | (const Iteravel& iteravel, Functor lambda) {
  if constexpr(is_same_v<invoke_result_t<Functor, decltype(*begin(iteravel))>, bool> == true) {
    vector<decay_t<decltype(*begin(iteravel))>> tempVetor;

    for (auto x : iteravel) {
      if (invoke(lambda, x)) {
        tempVetor.push_back(x);
      }
    }

    return tempVetor;
  } else if constexpr(is_same_v<invoke_result_t<Functor, decltype(*begin(iteravel))>, void> == false) {
    vector<decay_t<invoke_result_t<Functor, decltype(*begin(iteravel))>>> tempVetor;

    for (auto x : iteravel) {
      tempVetor.push_back(invoke(lambda, x));
    }

    return tempVetor;
  } else {
    for (auto x : iteravel) {
      lambda(x);
    }
  }
}