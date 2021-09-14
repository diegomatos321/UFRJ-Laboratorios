#include <memory>

using namespace std;

class Node {
  private:
    int data = 0;
    int height = 0;
    int level = 0;
  
  public:
    shared_ptr<Node> leftSubTree = nullptr;
    shared_ptr<Node> rightSubTree = nullptr;

    Node(int newData): data(newData) {};
    Node(int newData, int newHeight): data(newData), height(newHeight) {};
    Node(int newData, int newHeight, int newLevel): data(newData), height(newHeight), level(newLevel) {};

    int getData() const {
      return data;
    }

    void setHeight(int newHeight) {
      height = newHeight;
    }

    void setLevel(int newLevel) {
      level = newLevel;
    }
};

class BalancedBinarySearchTree {
  private:
    shared_ptr<Node> treeRoot = nullptr;
  
  public:
    BalancedBinarySearchTree() {}

    bool Search(int data) {
      return Search(treeRoot, data);
    }

    bool Search(shared_ptr<Node> root, int data) {
      if (root == nullptr)
        return false;
      if (data == root->getData())
        return true;
      if (data <= root->getData())
        return Search(root->leftSubTree, data);
      if (data >= root->getData())
        return Search(root->rightSubTree, data);
    } 

    void Insert(int data) {
      Insert(treeRoot, data);
    }

    void Insert(shared_ptr<Node> root, int data) {
      if (root == nullptr) {
        root = make_shared<Node>(data);
        return;
      }

      if (data <= root->getData()) {
        Insert(root->leftSubTree, data);
      } 
      else if (data > root->getData()) {
        Insert(root->rightSubTree, data);
      }
    }
};