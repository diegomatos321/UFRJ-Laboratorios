#include <iostream>
#include <vector>

using namespace std;

class Vertice {
  private:
    int value = 0;
    int grauDeEntrada = 0;
    vector<Vertice*> conexoes;

  public:
    Vertice() {};
    Vertice(int novoValor) : value(novoValor) {}
    Vertice(const Vertice &verticeCopia) : conexoes(verticeCopia.getConexoes()), value(verticeCopia.getValue()) {}

    void addConexao(Vertice* novaConexao)
    {
      conexoes.push_back(novaConexao);
    }

    void incrementGrauDeEntrada(int value)
    {
      grauDeEntrada += value;
    }

    vector<Vertice*> getConexoes() const
    {
      return conexoes;
    }

    int getValue() const
    {
      return value;
    }

    void setValue(int novoValor)
    {
      value = novoValor;
    }

    int getGrauEntrada()
    {
      return grauDeEntrada;
    }
};

class Grafo {
  private:
    int quantidadeDeVertices = 0;
    int quantidadeDeArestas = 0;
    vector<Vertice> listaDeVertices;

  public:
    Grafo(int novaQuantidadeDeVertices, int novaQuantidadeDeArestas)
    {
      quantidadeDeVertices = novaQuantidadeDeVertices;
      quantidadeDeArestas = novaQuantidadeDeArestas;
      
      for (size_t i = 0; i < quantidadeDeVertices; i++)
      {
        Vertice VerticeAtual(i + 1);
        listaDeVertices.push_back(VerticeAtual);
      } 
    }

    void print()
    {
      for (Vertice vertice : listaDeVertices)
      {
        cout << vertice.getValue();

        for (Vertice* conexao : vertice.getConexoes())
        {
          cout << " -> ";
          cout << conexao->getValue();
        }

        cout << endl;
      }
    }

    int getQuantidaDeVertices()
    {
      return quantidadeDeVertices;
    }

    Vertice* getVertice(int index)
    {
      return &listaDeVertices[index];
    }
};

void inicializarGrafo(Grafo &grafo);
vector<Vertice*> ordenacaoTopologica(Grafo &grafo);

int main()
{
  int quantidadeDeVertices = 0, quantidadeDeArestas = 0;

  scanf("%d %d", &quantidadeDeVertices, &quantidadeDeArestas);

  Grafo grafo(quantidadeDeVertices, quantidadeDeArestas);
  inicializarGrafo(grafo);

  grafo.print();

  vector<Vertice*> ordem = ordenacaoTopologica(grafo);
  for (Vertice* Vertice : ordem)
  {
    cout << Vertice->getValue() << " ";
  }
  cout << endl;

  return 0;
}

void inicializarGrafo(Grafo &grafo)
{
  for (int i = 0; i < grafo.getQuantidaDeVertices(); i++)
  {
    int index1 = 0, index2 = 0;
    Vertice* verticeAtual = grafo.getVertice(i);

    scanf("%d %d", &index1, &index2);

    if (index1)
    {
      Vertice *conexao1 = grafo.getVertice(index1 - 1);

      conexao1->incrementGrauDeEntrada(1);
      verticeAtual->addConexao(conexao1);

      if (index2)
      {
        Vertice *conexao2 = grafo.getVertice(index2 - 1);

        conexao2->incrementGrauDeEntrada(1);
        verticeAtual->addConexao(conexao2);
      }
    }
  }
}

vector<Vertice*> ordenacaoTopologica(Grafo &grafo)
{
  vector<Vertice*> ordemTopologica;
  vector<Vertice*> filaDeVerticesComGrauDeEntradaZero;

  for (int i = 0; i < grafo.getQuantidaDeVertices(); i++)
  {
    Vertice* verticeAtual = grafo.getVertice(i);
    if (verticeAtual->getGrauEntrada() == 0)
    {
      filaDeVerticesComGrauDeEntradaZero.push_back(verticeAtual);
    }
  }

  while (!filaDeVerticesComGrauDeEntradaZero.empty())
  {
    Vertice *vertice_n = filaDeVerticesComGrauDeEntradaZero.front();
    filaDeVerticesComGrauDeEntradaZero.erase(filaDeVerticesComGrauDeEntradaZero.begin());
    ordemTopologica.push_back(vertice_n);

    for (Vertice *conexao : vertice_n->getConexoes())
    {
      conexao->incrementGrauDeEntrada(-1);

      if (conexao->getGrauEntrada() == 0)
      {
        filaDeVerticesComGrauDeEntradaZero.push_back(conexao);
      }
    }
  }

  return ordemTopologica;
}
