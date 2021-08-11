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

template <typename Functor>
auto apply(int lista[], Functor callback) -> vector<decltype(callback(lista[0]))>
{
  vector<decltype(callback(lista[0]))> temp;
  int tamanhoDoArray = 5;

  for (int i = 0; i < tamanhoDoArray; i++)
  {
    temp.push_back(callback(lista[i]));
  }

  return temp;
}

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