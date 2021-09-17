#include <iostream>
#include <algorithm>
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

    int getHeight() const {
      return treeRoot->getHeight();
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
      int balancedFactor = 0;

      if (root == nullptr) {
        root = make_unique<Node>(data);
        return;
      }

      if (data <= root->getData())
        Insert(root->leftSubTree, data);
      else if (data > root->getData()) 
        Insert(root->rightSubTree, data);
      
      root->setHeight(calculateHeight(root));
      balancedFactor = getBalancedFactor(root);
    }

    int calculateHeight(unique_ptr<Node>& root) const {
      if (root->leftSubTree == nullptr && root->rightSubTree == nullptr)
        return 0;
      else if (root->leftSubTree != nullptr && root->rightSubTree == nullptr)
        return root->leftSubTree->getHeight() + 1;
      else if (root->leftSubTree == nullptr && root->rightSubTree != nullptr)
        return root->rightSubTree->getHeight() + 1;
      else if (root->leftSubTree != nullptr && root->rightSubTree != nullptr)
       return max(root->leftSubTree->getHeight(), root->rightSubTree->getHeight()) + 1;
    }

    int getBalancedFactor(unique_ptr<Node>& root) {
      if (root->leftSubTree == nullptr && root->rightSubTree == nullptr)
        return 0;
      else if (root->leftSubTree != nullptr && root->rightSubTree == nullptr)
        return root->leftSubTree->getHeight();
      else if (root->leftSubTree == nullptr && root->rightSubTree != nullptr)
        return -root->rightSubTree->getHeight();
      else if (root->leftSubTree != nullptr && root->rightSubTree != nullptr)
       return root->leftSubTree->getHeight() - root->rightSubTree->getHeight();
    }

    void preOrderPrint(unique_ptr<Node>& root) const {
      if (root == nullptr)
        return;

      cout << root->getData() << "(" << root->getHeight() << ")" << endl;
      inOrderPrint(root->leftSubTree);
      inOrderPrint(root->rightSubTree);
    }

    void inOrderPrint(unique_ptr<Node>& root) const {
      if (root == nullptr)
        return;

      inOrderPrint(root->leftSubTree);
      cout << root->getData() << "(" << root->getHeight() << ")" << endl;
      inOrderPrint(root->rightSubTree);
    }

    void postOrderPrint(unique_ptr<Node>& root) const {
      if (root == nullptr)
        return;

      inOrderPrint(root->leftSubTree);
      inOrderPrint(root->rightSubTree);
      cout << root->getData() << "(" << root->getHeight() << ")" << endl;
    }
};