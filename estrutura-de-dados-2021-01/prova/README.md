# Respostas da prova de Estrutura de Dados - 2021.02
* Aluno: Diego Vasconcelos Schardosim de Matos
* Dre: 120098723

## Questão 1: 
Algoritmo de inserção para uma lista encadeada, ordenada (em ordem crescente), sem dependender do nó cabeça.
```C++
void insert(int data, Node** currentNode) {
  if(*currentNode == nullptr) {
    *currentNode = new Node(data);
    return;
  }

  if(data <= (*currentNode)->data) {
    Node* tempNode = *currentNode;
    Node* newNode = new Node(data);

    *currentNode = newNode;
    newNode->next = tempNode;
  } else {
    insert(data, &(*currentNode)->next);
  }
}
```
