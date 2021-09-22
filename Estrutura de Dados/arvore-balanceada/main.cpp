#include<iostream>

#include "balanced-binary-search-tree.cpp"

using namespace std;

int main() {
  BalancedBinarySearchTree myTree;
  myTree.Insert(10);
  myTree.Insert(20);
  myTree.inOrderPrint();
  myTree.Insert(30);

  myTree.preOrderPrint();
  // myTree.inOrderPrint();
  // myTree.postOrderPrint();
  return EXIT_SUCCESS;
}