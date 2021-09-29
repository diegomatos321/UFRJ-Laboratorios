#include<iostream>

using namespace std;

template <int Linhas, int Colunas>
class Matriz {
  private:
    double matriz[Linhas][Colunas];
  
  public:
    Matriz() {
      for (int linha = 0; linha < Linhas; linha++) {
        for (int coluna = 0; coluna < Colunas; coluna++) {
          matriz[linha][coluna] = 0;
        }
      }
    }

    int nLin() const {
      return Linhas;
    }
    
    int nCol() const {
      return Colunas;
    }

    double* operator [] (int index) {
      return matriz[index];
    }
    
    Matriz<Linhas, Colunas> operator + (Matriz<Linhas, Colunas>& matrizParaSomar) {
      Matriz<Linhas, Colunas> MatrizResultado;

      for (int linha = 0; linha < Linhas; linha++) {
        for (int coluna = 0; coluna < Colunas; coluna++) {
          MatrizResultado[linha][coluna] = matriz[linha][coluna] + matrizParaSomar[linha][coluna];
        }
      }

      return MatrizResultado;
    }

    template<int Matriz2Colunas>
    Matriz<Linhas, Matriz2Colunas> operator * (Matriz<Colunas, Matriz2Colunas>& matrizParaMultiplicar) {
      Matriz<Linhas, Matriz2Colunas> MatrizResultado;

      for (int linha = 0; linha < Linhas; linha++) {
        for (int coluna = 0; coluna < Colunas; coluna++) {
          MatrizResultado[linha][coluna] = 0;

          for (int i = 0; i < Colunas; i++) {
            MatrizResultado[linha][coluna] += matriz[linha][i] * matrizParaMultiplicar[i][coluna];
          }  
        }
      }
      
      return MatrizResultado;
    }
};

template<int LinhaMatrizA, int ColunaMatrizA, int ColunaMatrizB>
class Otimizador {
  private:
    Matriz<LinhaMatrizA, ColunaMatrizA> matrizA;
    Matriz<ColunaMatrizA, ColunaMatrizB> matrizB;

  public:
    Otimizador(const Matriz<LinhaMatrizA, ColunaMatrizA>& a, const Matriz<ColunaMatrizA, ColunaMatrizB>& b): matrizA(a), matrizB(b) {}

    template<int ColunaMatrizC>
    Matriz<LinhaMatrizA, ColunaMatrizC> otimizar (const Matriz<ColunaMatrizB, ColunaMatrizC>& matrizC) {
      Matriz<LinhaMatrizA, ColunaMatrizC> matrizResultado;

      if (LinhaMatrizA * ColunaMatrizB < ColunaMatrizA * ColunaMatrizC) {
        matrizResultado = (matrizA * matrizB) * matrizC;
      } else {
        matrizResultado = matrizA * (matrizB * matrizC);
      }

      return matrizResultado;
    }
};

template<int LinhaMatrizA, int ColunaMatrizA, int ColunaMatrizB>
Otimizador<LinhaMatrizA, ColunaMatrizA, ColunaMatrizB> operator * (const Matriz<LinhaMatrizA, ColunaMatrizA>& matrizA, const Matriz<ColunaMatrizA, ColunaMatrizB>& matrizB) {
  return Otimizador<LinhaMatrizA, ColunaMatrizA, ColunaMatrizB>(matrizA, matrizB);
};

template<int LinhaMatrizA, int ColunaMatrizA, int LinhaMatrizC, int ColunaMatrizC>
Matriz<LinhaMatrizA, ColunaMatrizC> operator * (Otimizador<LinhaMatrizA, ColunaMatrizA, LinhaMatrizC>& otimizador, const Matriz<LinhaMatrizC, ColunaMatrizC>& matrizC) {
  return otimizador.otimizar(matrizC);
};

template <typename Functor>
class Apply {
  private:
    Functor lambda;

  public:
    Apply(Functor functor): lambda(functor) {}
    
    template <int Linhas, int Colunas>
    Matriz<Linhas, Colunas> operator () ( Matriz<Linhas, Colunas>& matriz ) const {
      Matriz<Linhas, Colunas> matrizResultado;

      for (int linha = 0; linha < Linhas; linha++)
      {
        for (int coluna = 0; coluna < Colunas; coluna++)
        {
          matrizResultado[linha][coluna] = lambda(matriz[linha][coluna]);
        }
      }
      
      return matrizResultado;
    }
};