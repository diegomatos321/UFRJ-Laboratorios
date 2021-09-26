#include<iostream>

using namespace std;

template <int Linhas, int Colunas>
class Matriz {
  private:
    double matriz[Colunas][Linhas];
  
  public:
    Matriz() {
      for (int linha = 0; linha < Linhas; linha++)
      {
        for (int coluna = 0; coluna < Colunas; coluna++)
        {
          matriz[linha][coluna] = linha + coluna;
        }
      }
    }

    double* operator [] (int index) {
      return matriz[index];
    }
    
    Matriz<Linhas, Colunas> operator + (Matriz<Linhas, Colunas>& matrizParaSomar) {
      Matriz<Linhas, Colunas> MatrizResultado;

      for (int linha = 0; linha < Linhas; linha++)
      {
        for (int coluna = 0; coluna < Colunas; coluna++)
        {
          MatrizResultado[linha][coluna] = matriz[linha][coluna] + matrizParaSomar[linha][coluna];
        }
      }

      return MatrizResultado;
    }

    template<int Matriz2Colunas>
    Matriz<Linhas, Matriz2Colunas> operator * (Matriz<Colunas, Matriz2Colunas>& matrizParaMultiplicar) {
      Matriz<Linhas, Matriz2Colunas> MatrizResultado;

      for (int linha = 0; linha < Linhas; linha++)
      {
        for (int coluna = 0; coluna < Colunas; coluna++)
        {
          MatrizResultado[linha][coluna] = 0;

          for (int i = 0; i < Colunas; i++)
          {
            MatrizResultado[linha][coluna] = matriz[linha][i] * matrizParaMultiplicar[i][coluna];
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
    // Matriz<LinhaMatrizA, ColunaMatrizB> matrizOtimizada;
    bool done = false;

  public:
    Otimizador(const Matriz<LinhaMatrizA, ColunaMatrizA>& a, const Matriz<ColunaMatrizA, ColunaMatrizB>& b): matrizA(a), matrizB(b) {}

    template<int ColunaMatrizC>
    Matriz<LinhaMatrizA, ColunaMatrizC> otimizar (const Matriz<ColunaMatrizB, ColunaMatrizC>& matrizC) {
      Matriz<LinhaMatrizA, ColunaMatrizC> matrizResultado;

      if (LinhaMatrizA * ColunaMatrizB < ColunaMatrizA * ColunaMatrizC || done) {
        matrizResultado = (matrizA * matrizB) * matrizC;
      } else {
        matrizResultado = matrizA * (matrizB * matrizC);
      }

      return matrizResultado;
    }

    /* operator Matriz<LinhaMatrizA, ColunaMatrizB> () {
      return matrizA * matrizB;
    } */
};

template<int Linhas, int Colunas>
ostream& operator << (ostream& out, Matriz<Linhas, Colunas> matriz) {
  for (int linha = 0; linha < Linhas; linha++)
  {
    for (int coluna = 0; coluna < Colunas; coluna++)
    {
      out << "(" << matriz[linha][coluna] << ")" << linha << "x" << coluna << " ";
    }
    out << endl;
  }
  out << endl;

  return out;
}


template<int LinhaMatrizA, int ColunaMatrizA, int ColunaMatrizB>
Otimizador<LinhaMatrizA, ColunaMatrizA, ColunaMatrizB> operator * (const Matriz<LinhaMatrizA, ColunaMatrizA>& matrizA, const Matriz<ColunaMatrizA, ColunaMatrizB>& matrizB) {
  return Otimizador<LinhaMatrizA, ColunaMatrizA, ColunaMatrizB>(matrizA, matrizB);
};

template<int LinhaMatrizA, int ColunaMatrizA, int LinhaMatrizC, int ColunaMatrizC>
Matriz<LinhaMatrizA, ColunaMatrizC> operator * (const Otimizador<LinhaMatrizA, ColunaMatrizA, LinhaMatrizC>& otimizador, const Matriz<LinhaMatrizC, ColunaMatrizC>& matrizC) {
  return otimizador.otimizar(matrizC);
};

/* template <typename Functor>
class Apply {
public:
  Apply(Functor lambda): functor(lambda) {}
  
  template <int Linhas, int Colunas>
  Matriz<Linhas, Colunas> operator()( const Matriz<Linhas, Colunas>& m ) const {
  }
  
private:
  Functor functor;
}; */