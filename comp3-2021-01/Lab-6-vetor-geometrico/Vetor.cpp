#include <iostream>
#include <type_traits>

using namespace std;

template<int Dimensoes, typename Tipo> class Vetor;

template<int Dimensoes, typename Tipo>
class MeioDaOperacaoAtribuicao {
  private:
    Vetor<Dimensoes, Tipo>* vetor;
  
  public:
    MeioDaOperacaoAtribuicao(Vetor<Dimensoes, Tipo>* ptrVetor): vetor(ptrVetor) {}
/*     ~MeioDaOperacaoAtribuicao() {
      delete vetor;
    } */

    MeioDaOperacaoAtribuicao operator , (Tipo coordenada) {
      *vetor = coordenada;
      return *this;
    }
};

template<int Dimensoes, typename Tipo>
class MeioDoProdutoVetorial {
  private:
    Vetor<Dimensoes, Tipo>* vetor;
  
  public:
    MeioDoProdutoVetorial(Vetor<Dimensoes, Tipo>* ptrVetor): vetor(ptrVetor) {}
/*     ~MeioDoProdutoVetorial() {
      delete vetor;
    } */

    MeioDoProdutoVetorial operator * (Vetor<Dimensoes, Tipo>& vetorB) {
      *vetor * vetorB;

      return *this;
    }

    void imprime(ostream& out) {
      vetor->imprime(out);
    }
};

template<int Dimensoes, typename Tipo>
class Vetor {
  private:
    Tipo coordenadas[Dimensoes];
    int index = 0;
  
  public:
    Vetor(){
      for (int i = 0; i < Dimensoes; i++)
      {
        coordenadas[i] = 0;
      }
    }

    void imprime( ostream& out ) const {
      for( Tipo x : coordenadas ) 
        out << x << " ";
    }

    MeioDaOperacaoAtribuicao<Dimensoes, Tipo> operator = (Tipo coordenada) {
      if (index < Dimensoes) {
        coordenadas[index] = coordenada;
        index++;
      }

      return MeioDaOperacaoAtribuicao<Dimensoes, Tipo>(this);
    }

    Tipo& operator [] (int i) {
      if (i > Dimensoes) {
        exit(1);
      }

      return coordenadas[i];
    }

    Vetor operator + (Vetor<Dimensoes, Tipo>& vetorB) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] + vetorB[i];
      }
      
      return novoVetor;
    }

    template<typename Numerico, typename = typename enable_if<is_arithmetic<Numerico>::value>::type>
    Vetor operator + (Numerico escalar) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] + escalar;
      }
      
      return novoVetor;
    }

    Vetor operator - (Vetor<Dimensoes, Tipo>& vetorB) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] - vetorB[i];
      }
      
      return novoVetor;
    }

    template<typename Numerico, typename = typename enable_if<is_arithmetic<Numerico>::value>::type>
    Vetor operator - (Numerico escalar) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] - escalar;
      }
      
      return novoVetor;
    }

    MeioDoProdutoVetorial<Dimensoes, Tipo> operator * (Vetor<Dimensoes, Tipo>& vetorB) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] * vetorB[i];
      }
      
      return MeioDoProdutoVetorial<Dimensoes, Tipo>(this);
    }

    template<typename Numerico, typename = typename enable_if<is_arithmetic<Numerico>::value>::type>
    MeioDoProdutoVetorial<Dimensoes, Tipo> operator * (Numerico escalar) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] * escalar;
      }
      
      return MeioDoProdutoVetorial<Dimensoes, Tipo>(this);
    }
};

template<int Dimensoes, typename Tipo>
ostream& operator << ( ostream& out, const Vetor<Dimensoes,Tipo>& v) {
  v.imprime( out );

  return out;
}

template<int Dimensoes, typename Tipo>
ostream& operator << ( ostream& out, const MeioDoProdutoVetorial<Dimensoes,Tipo>& v) {
  v.imprime( out );

  return out;
}