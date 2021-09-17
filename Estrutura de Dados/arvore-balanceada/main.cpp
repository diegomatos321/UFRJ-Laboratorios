#include<iostream>

#include "balanced-binary-search-tree.cpp"

using namespace std;

int main() {
  BalancedBinarySearchTree myTree;
  myTree.Insert(10);
  myTree.Insert(15);
  myTree.Insert(14);
  myTree.Insert(16);
  myTree.Insert(7);
  myTree.Insert(8);
  myTree.Insert(5);

  // myTree.preOrderPrint();
  myTree.inOrderPrint();
  cout << myTree.getHeight() << endl;
  // myTree.postOrderPrint();
  return 0;
}