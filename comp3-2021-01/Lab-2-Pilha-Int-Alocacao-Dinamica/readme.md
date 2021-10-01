# Lab 2 - Pilha Int Dinamica

1. Um constructor com um parâmetro capacidade (o tamanho da pilha) que deverá alocar dinamicamente o array que irá armazenar a pilha, usando malloc e inicializado com zeros - esse construtor irá ter um valor default igual a 10;
   1. Valores default são indicados através de uma atribuição no cabeçalho da rotina: PilhaInt( int tamanho = 10 ) { ... }
2. Um copy constructor, que irá criar uma cópia do array alocado, contendo os mesmos elementos da pilha anterior;
3. Um destructor que irá desalocar o ponteiro alocado no constructor;
4. Um operador de atribuição com o comportamento descrito acima;
5. Um método capacidade() que retorna a capacidade da pilha;
6. Um método redimensiona(int n), que altera a capacidade da pilha. Se a nova capacidade for menor do que o número de elementos atualmente na pilha deve-se desempilhar o número suficiente de elementos para adequar a pilha à nova capacidade.
7. Sempre que a pilha estourar (o topo ultrapassar a capacidade) ela deve ser realocada com o dobro do tamanho atual;