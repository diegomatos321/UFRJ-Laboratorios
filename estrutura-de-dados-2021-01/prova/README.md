# Respostas da prova de Estrutura de Dados - 2021.02
* Aluno: Diego Vasconcelos Schardosim de Matos
* Dre: 120098723

## Questão 1: 
Algoritmo de inserção para uma lista encadeada, ordenada (escolhi em ordem crescente), sem dependender do nó cabeça.
```C++
class Node {
  public:
    int data = 0;
    Node* next = nullptr;

    Node(int data): data(data) {}
    ~Node() {
      delete next;
    }
};

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

## Questão 2:
2.1) Algoritmo que preenche, para **cada nó** da árvore, o campo soma, que deve conter a soma de todas as chaves que estão na subárvore, incluindo sua propria chave.
```C++
class Node {
  public:
    Node* esquerda = nullptr;
    Node* direita = nullptr;
    int chave = 0;
    int soma = 0;

    Node(int chave): chave(chave), soma(chave) {}
    ~Node() {
      delete esquerda;
      delete direita;
    }

    // Supondo que o valor da propria raiz foi corretamente incluída
    // Durante a inserção
    void calculateSoma() {
      soma = esquerda->soma + direita->soma;
    }
};
```

2.2) Escreva um algoritmo eficiente que insira uma chave nesta arvore e que atualize no processo o campo soma.
```C++
void Insert(int data, Node** currentNode) {
  if(*currentNode == nullptr) {
    *currentNode = new Node(data);
    return;
  }

  if(data <= (*currentNode)->chave) {
    Insert(data, &(*currentNode)->esquerda);
  } else {
    Insert(data, &(*currentNode)->direita);
  }

  (*currentNode)->soma += data;
}
```