#include <memory>

using namespace std;

class Node {
  private:
    int data = 0;
    int height = 0;
    int level = 0;
  
  public:
    unique_ptr<Node> leftSubTree = nullptr;
    unique_ptr<Node> rightSubTree = nullptr;
    
    Node(int newData): data(newData) {};
    Node(int newData, int newHeight): data(newData), height(newHeight) {};
    Node(int newData, int newHeight, int newLevel): data(newData), height(newHeight), level(newLevel) {};

    int getData() const {
      return data;
    }

    void setHeight(int newHeight) {
      height = newHeight;
    }

    int getHeight() const {
      return height;
    }

    void setLevel(int newLevel) {
      level = newLevel;
    }

    int getLevel() const {
      return level;
    }
};

class BalancedBinarySearchTree {
  private:
    unique_ptr<Node> treeRoot = nullptr;
  
  public:
    BalancedBinarySearchTree() {}

    bool Search(int data) {
      return Search(treeRoot, data);
    }

    void Insert(int data) {
      Insert(treeRoot, data);
    }

    void preOrderPrint() {
      preOrderPrint(treeRoot);
    }

    void inOrderPrint() {
      inOrderPrint(treeRoot);
    }

    void postOrderPrint() {
      postOrderPrint(treeRoot);
    }
  
  private:
    bool Search(unique_ptr<Node>& root, int data) const {
      if (root == nullptr)
        return false;
      if (data == root->getData())
        return true;
      if (data <= root->getData())
        return Search(root->leftSubTree, data);
      if (data >= root->getData())
        return Search(root->rightSubTree, data);
    }

    void Insert(unique_ptr<Node>& root, int data) {
      if (root == nullptr) {
        root = make_unique<Node>(data);
        return;
      }

      if (data <= root->getData()) 
        Insert(root->leftSubTree, data);
      else if (data > root->getData())
        Insert(root->rightSubTree, data);
    }

    void preOrderPrint(unique_ptr<Node>& root) const {
      if (root == nullptr)
        return;

      cout << root->getData() << endl;
      inOrderPrint(root->leftSubTree);
      inOrderPrint(root->rightSubTree);
    }

    void inOrderPrint(unique_ptr<Node>& root) const {
      if (root == nullptr)
        return;

      inOrderPrint(root->leftSubTree);
      cout << root->getData() << endl;
      inOrderPrint(root->rightSubTree);
    }

    void postOrderPrint(unique_ptr<Node>& root) const {
      if (root == nullptr)
        return;

      inOrderPrint(root->leftSubTree);
      inOrderPrint(root->rightSubTree);
      cout << root->getData() << endl;
    }
};