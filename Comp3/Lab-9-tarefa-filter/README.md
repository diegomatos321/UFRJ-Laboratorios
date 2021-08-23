# Tarefa Filter

Acrescentar na tarefa anterior o conceito de filter. Um filter é um predicado que retorna bool, e somente repassa para o próximo "pipe" os elementos que retornarem verdadeiro.

Usando o exempla tarefa Stream:

```C++
v | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << endl; };
Irá imprimir apenas os números pares. 
```