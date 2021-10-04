#include <iostream>

using namespace std;

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

    // Supondo que o valor da propria raiz foi corretamente incluida
    // Durante a inserção
    void calculateSoma() {
      if(esquerda != nullptr && direita == nullptr)
        soma = esquerda->soma + chave;
      else if(esquerda == nullptr && direita != nullptr)
        soma = direita->soma + chave;
      else
        soma = esquerda->soma + direita->soma + chave;
    }
};

class ArvoreBinariaDeBusca {
  private:
    Node* treeRoot = nullptr;

  public:
    ArvoreBinariaDeBusca() {}
    ~ArvoreBinariaDeBusca() {
      delete treeRoot;
    }

    void Insert(int data) {
      Insert(data, &treeRoot);
    }

    void inOrderPrint() const {
      inOrderPrint(treeRoot);
    }
  
  private:
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

      // (*currentNode)->soma += data;
      (*currentNode)->calculateSoma();
    }

    void inOrderPrint(Node* root) const {
      if (root == nullptr)
        return;

      inOrderPrint(root->esquerda);
      cout << root->chave << "(" << root->soma << ") ";
      inOrderPrint(root->direita);
    }
};

int main() {
  ArvoreBinariaDeBusca arvore;

  arvore.Insert(10);
  arvore.Insert(20);
  arvore.Insert(7);
  arvore.Insert(1);
  arvore.Insert(8);
  arvore.Insert(15);
  arvore.Insert(31);
  arvore.Insert(12);

  arvore.inOrderPrint();

  return EXIT_SUCCESS;
}