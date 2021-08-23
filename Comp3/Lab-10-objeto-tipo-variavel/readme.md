# Objeto com tipo variável

O objetivo desse trabalho é criar uma classe Var semelhante às variáveis do Javascript, que podem receber valores de vários tipos diferentes e durante a execução vão mudando internamente de tipo. Assim, uma variável pode ser criada como string e depois um double pode lhe ser atribuído, mudando o seu tipo. Se ela for um objeto, pode ter atributos que podem ser outras variáveis ou mesmo funções - semelhante ao que ocorre é Javascript. Nesse momento pense apenas na clareza, elegância e facilidade de implementação - ignore qualquer tentativa de otimização que possa surgir na sua mente durante a codificação.  Um exemplo de uso segue abaixo:

```C++
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

int main() {
  Var a, b;
  
  cout << a << endl; // saída: "undefined"
  a = 1;
  cout << a << endl; // saída: 1
  a = "hello";
  cout << a << endl; // saída: hello
  
  a = newObject();
  a["atr"] = 9;
  a["metodo"] = []( auto x ){ return x*x; };
  b = 4;
  cout << a["metodo"]( b ) << endl; // Saída: 16;
}
```