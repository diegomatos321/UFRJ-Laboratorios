#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <memory>

#include "balanced-binary-search-tree.cpp"

#define BASE_HEIGHT 1

using namespace std;

int main() {
  BalancedBinarySearchTree myTree;
  string str;
  int num = 0;

  while(!feof(stdin)) {
    if (scanf("%s", &str[0]) == 1) {
      if (str[0] == 'i') {
        if (scanf("%d", &num) == 1) {
          myTree.Insert(num);
        }
      } 
      if(str[0] == 'p') {
        myTree.preOrderPrint();
        cout << endl;
      }
    }
  }

  return EXIT_SUCCESS;
}