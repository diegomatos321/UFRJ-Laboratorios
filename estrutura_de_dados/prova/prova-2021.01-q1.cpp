#include <iostream>

using namespace std;

class Node {
  public:
    int data = 0;
    Node* next = nullptr;

    Node(int data): data(data) {}
    ~Node() {
      delete next;
    }
};

class ListaEncadeadaOrdenada {
  private:
    Node* inicio = nullptr;
  
  public:
    ~ListaEncadeadaOrdenada() {
      delete inicio;
    }

    void insert(int data) {
      insert(data, &inicio);
    }

    void print() {
      print(inicio);
      cout << endl;
    }

  private:
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

    void print(Node* node) {
      if(node == nullptr)
        return;
      
      cout << node->data << " ";
      print(node->next);
    }
};

int main() {
  ListaEncadeadaOrdenada listaTeste;

  listaTeste.insert(10);
  listaTeste.insert(5);
  listaTeste.insert(7);
  listaTeste.insert(1);
  listaTeste.insert(11);

  listaTeste.print();

  return EXIT_SUCCESS;
}