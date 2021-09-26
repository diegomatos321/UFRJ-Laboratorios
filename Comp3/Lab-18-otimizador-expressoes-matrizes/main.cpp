#include<iostream>

#include "otimizador.cpp"

using namespace std;

int main() {
  Matriz<10,20> matrizA;
  Matriz<10,20> matrizB;

  auto matrizResultado = matrizA + matrizB;

  cout << matrizResultado;
  
  return 0;  
}