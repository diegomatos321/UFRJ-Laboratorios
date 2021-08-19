using namespace std;

template<int Dimensoes, typename Tipo> class Vetor;

template<int Dimensoes, typename Tipo>
class MeioDaOperacaoAtribuicao {
  private:
    Vetor<Dimensoes, Tipo>* vetor;
  
  public:
    MeioDaOperacaoAtribuicao(Vetor<Dimensoes, Tipo>* ptrVetor): vetor(ptrVetor) {}
    ~MeioDaOperacaoAtribuicao() {
      delete vetor;
    }

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
    ~MeioDoProdutoVetorial() {
      delete vetor;
    }

    MeioDoProdutoVetorial operator * (Vetor<Dimensoes, Tipo>& vetorB) {
      return *vetor * vetorB;;
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
/*     Vetor(Vetor& vetorCopia): index(vetorCopia.index) {
      cout << "Construtor de Cópia ";
      imprime(cout);
      cout << endl;
      for (int i = 0; i < Dimensoes; i++)
      {
        coordenadas[i] = vetorCopia[i];
      }
    }
 */
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
        cout << "Index fora do tamanho" << endl;
        exit(1);
      }

      return coordenadas[i];
    }

    // ToDo: Criar produto vetorial
    Vetor<Dimensoes, Tipo> operator * (Vetor<Dimensoes, Tipo>& vetor) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] * vetor[i];
      }

      return novoVetor;
    }

    template<typename T>
    Vetor operator * (T numero) {
      Vetor<Dimensoes, T> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] * numero;
      }

      return novoVetor;
    }

    Vetor operator / (Vetor<Dimensoes, Tipo>& vetor) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] / vetor[i];
      }
      
      return novoVetor;
    }

    template<typename T>
    Vetor operator / (T numero) {
      Vetor<Dimensoes, T> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] / numero;
      }
      
      return novoVetor;
    }
    
    Vetor operator + (Vetor<Dimensoes, Tipo>& vetor) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] + vetor[i];
      }
      
      return novoVetor;
    }

    template<typename T>
    Vetor operator + (T numero) {
      Vetor<Dimensoes, T> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] + numero;
      }
      
      return novoVetor;
    }

    Vetor operator - (Vetor<Dimensoes, Tipo>& vetor) {
      Vetor<Dimensoes, Tipo> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] - vetor[i];
      }
      
      return novoVetor;
    }

    template<typename T>
    Vetor operator - (T numero) {
      Vetor<Dimensoes, T> novoVetor;

      for (int i = 0; i < Dimensoes; i++)
      {
        novoVetor[i] = coordenadas[i] - numero;
      }
      
      return novoVetor;
    }
};

template<int Dimensoes, typename Tipo>
ostream& operator << ( ostream& out, const Vetor<Dimensoes,Tipo>& v) {
  v.imprime( out );

  return out;
}