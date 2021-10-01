# Tarefa Stream

Implementar uma template que torne possível o seguinte tipo de código:
```C++
int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
vector<int> v{ 2 , 6, 8 };
tab | []( int x ) { cout << x*x << endl; };
tab | [ &v ]( int x ) { v.push_back( x ); };
v | []( int x ) { cout << x*x << endl; };
v | &print;
```

Onde print é uma função que recebe um int. 
```C++
void print( int x ) { cout << x << " "; }
```

Esse operador será equivalente a:
```
for_each( tab, tab+10,  []( int x ) { cout << x*x << endl; } );
```