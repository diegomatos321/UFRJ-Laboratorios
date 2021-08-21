# Lab 3 - Print com lista de tuplas

Faça uma template ou função "print" que recebe um lista de pares de tipos variáveis e as imprime. Isso pode ser feito usando pair ou tuple com dois elementos.

Um exemplo de declaração seria:
```
int main() {
 
  print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );
  
  return 0;  
}
```

Que deve imprimir:
```
jan = 1
2 = fev
pi = 3.14
```