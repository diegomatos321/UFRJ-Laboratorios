#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Vertice {
  private:
    int value;
    int grauDeEntrada;
    vector<Vertice*> conexoes;

  public:
    Vertice() {};
    Vertice(int novoValor) : value(novoValor) {}
    Vertice(const Vertice &verticeCopia) : value(verticeCopia.getValue()), conexoes(verticeCopia.getConexoes()) {}

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
      
      for (int i = 0; i < quantidadeDeVertices; i++)
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

void lerEntradasNoGrafo(Grafo &grafo);
vector<Vertice*> ordenacaoTopologica(Grafo &grafo);

int main()
{
  int quantidadeDeVertices = 0, quantidadeDeArestas = 0;

  scanf("%d %d", &quantidadeDeVertices, &quantidadeDeArestas);

  Grafo grafo(quantidadeDeVertices, quantidadeDeArestas);
  lerEntradasNoGrafo(grafo);

  // grafo.print();

  vector<Vertice*> ordem = ordenacaoTopologica(grafo);
  for (Vertice* Vertice : ordem)
  {
    cout << Vertice->getValue() << " ";
  }
  cout << endl;

  return 0;
}

void lerEntradasNoGrafo(Grafo &grafo)
{
  string linha;
  
  for (int i = -1; i < grafo.getQuantidaDeVertices(); i++)
  {
    int pos = 0, numLido = 0, numChars = 0;

    getline(cin, linha);
    
    while (sscanf(&linha[pos], "%d %n", &numLido, &numChars) > 0) 
    {
      pos += numChars;

      if(linha.length() != 0)
      {
        Vertice* verticeAtual = grafo.getVertice(i);
        Vertice* conexao = grafo.getVertice(numLido-1);

        conexao->incrementGrauDeEntrada(1);
        verticeAtual->addConexao(conexao);
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
