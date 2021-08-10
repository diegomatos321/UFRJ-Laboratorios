#include <vector>
#include <initializer_list>

using namespace std;

template <typename TipoA, typename Functor>
auto apply(TipoA lista, Functor callback) -> vector<decltype(callback(lista[0]))>
{
  vector<decltype(callback(lista[0]))> temp;

  for (auto x : lista)
  {
    temp.push_back(callback(x));
  }

  return temp;
}

/* template <typename TipoA>
vector<double> apply(TipoA lista, double (*callback)(int))
{
  vector<double> temp;

  for (auto x : lista)
  {
    temp.push_back(callback(x));
  }

  return temp;
} */

template <typename Functor>
auto apply(initializer_list<int> lista, Functor callback) -> vector<decltype(callback(*lista.begin()))>
{
  vector<decltype(callback(*lista.begin()))> temp;

  for (auto x : lista)
  {
    temp.push_back(callback(x));
  }

  return temp;
}