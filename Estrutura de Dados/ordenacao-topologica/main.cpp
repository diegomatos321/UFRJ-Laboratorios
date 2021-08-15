#include <iostream>
#include <vector>

using namespace std;

class Node {
  private:
    int value = 0;
    Node* next = nullptr;
  
  public:
    Node(int novoValor): value(novoValor) {}
    Node(const Node& noCopia) {
      Node* auxNode = noCopia.getNextNode();

      value = noCopia.getValue();

      next = new Node(auxNode->getValue());
      next->setNextNode(auxNode->getNextNode());
    }
    ~Node() {
      delete next;
    }

    void setNextNode(Node* newNext) {
      next = newNext;
    }

    Node* getNextNode() const {
      return next;
    }

    int getValue() const {
      return value;
    }
};

void inicializarGrafo(vector<Node*> grafo, unsigned int quantidadeDeNos);
void printNode(Node* noAtual);
void printGrafo(vector<Node*> grafo);

int main() {
  unsigned int quantidadeDeNos = 0;
  vector<Node*> grafo;

  scanf("%d %d", &quantidadeDeNos);

  inicializarGrafo(grafo, quantidadeDeNos);

  printGrafo(grafo);

  return 0;
}

void inicializarGrafo(vector<Node*> grafo, unsigned int quantidadeDeNos) {
  for (size_t i = 1; i <= quantidadeDeNos; i++)
  {
    Node* noAtual = new Node(i);
    int value1 = 0, value2 = 0;

    scanf("%d %d", &value1, &value2);

    if (value1) {
      Node* conexao1 = new Node(value1);
      noAtual->setNextNode(conexao1);

      if (value2) {
        Node* conexao2 = new Node(value2);
        conexao1->setNextNode(conexao2);
      }
    }

    grafo.push_back(noAtual);
  }
}

void printGrafo(vector<Node*> grafo) {
  for (Node* noAtual : grafo) {
    printNode(noAtual);
  }
}

void printNode(Node* noAtual) {
  cout << noAtual->getValue();

  if (noAtual->getNextNode() == nullptr) {
    cout << endl;
    return;
  }
  else {
    cout << " -> ";
    printNode(noAtual->getNextNode());
  }
}