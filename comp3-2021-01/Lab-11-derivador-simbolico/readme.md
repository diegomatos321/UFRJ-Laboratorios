# Tarefa - Derivador Simbólico

Nesta tarefa você deve criar templates, funções e operadores para permitir a criação de um derivador simbólico. A idéia é que você possa definir uma fórmula para uma função que recebe um parâmetro x e essa função possa ser chamada através do método **e** (passando um valor para x), e calculando também o valor da derivada dela em relação a x através do método dx.

Exemplos:
```C++
int main() {
  auto f = 3.0 * x * x;
  double v = 7;
  
  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}
```

Saída esperada:
```
f(7)=147, f'(7)=42
```

Além das expressões com os operadores aritméticos simples +, -, * e /, implementar as funções exp, log, sin e cos. Lembre-se de usar a regra da cadeia para sin(f(x)) funcionar.

Redefina o operador "->*" para aceitar int, significando:
```C++
x->*2 ==> x²
```

Gere um erro de compilação se "->*" for usado com um double: x->*0.5, por exemplo. A mensagem do erro deve ser: "Operador de potenciação definido apenas para inteiros".
