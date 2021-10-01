#include <stdio.h>

int num = 5;
static int val = 9;

int func(int a, int b){
  a = (a + b) / 2;
  printf("%i %i %i\n", num, a, b);
  num -= a;
  return a;
}

int main() {
  int a = 0, b = 50;
  num = 10;
  num += func(a, b);
  {
    int a = 10, b = 20;
    printf("%i %i %i\n", num, a, b);
    num += func(a, b);
  }

  printf("%i %i %i\n", num, a, b);
  return 0;
}