#include <iostream>
#include <vector>

using namespace std;

class Node {
  private:
    int value = 0;
    int grauDeEntrada = 0;
    vector<Node*> conexoes;
  
  public:
    Node(int novoValor): value(novoValor) {}
    Node(const Node& noCopia): conexoes(noCopia.getConexoes()) {
      value = noCopia.getValue();
    }

    void addConexao(Node* novaConexao) {
      conexoes.push_back(novaConexao);
    }

    void incrementGrauDeEntrada(int value) {
      grauDeEntrada += value;
    }

    vector<Node*> getConexoes() const {
      return conexoes;
    }

    int getValue() const {
      return value;
    }

    void setValue(int novoValor) {
      value = novoValor;
    }

    int getGrauEntrada() {
      return grauDeEntrada;
    }
};

void inicializarGrafo(vector<Node>& grafo, unsigned int quantidadeDeNos);
vector<Node*> ordenacaoTopologica(vector<Node>& grafo, unsigned int quantidadeDeNos);
void printGrafo(const vector<Node>& grafo);
void printNode(const Node& noAtual);

int main() {
  unsigned int quantidadeDeNos = 0;

  scanf("%d %d", &quantidadeDeNos);

  Node arestaReferencia(0);
  vector<Node> grafo(quantidadeDeNos, arestaReferencia);
  inicializarGrafo(grafo, quantidadeDeNos);

  printGrafo(grafo);

  vector<Node*> ordem = ordenacaoTopologica(grafo, quantidadeDeNos);
  for (unsigned int i = 0; i < quantidadeDeNos; i++)
  {
    cout << ordem[i]->getValue() << ", ";
  }
  cout << endl;

  return 0;
}

void inicializarGrafo(vector<Node>& grafo, unsigned int quantidadeDeNos) {
  for (size_t i = 0; i < quantidadeDeNos; i++)
  {
    int value1 = 0, value2 = 0;
    grafo[i].setValue(i+1);

    scanf("%d %d", &value1, &value2);

    if (value1) {
      // Node* conexao1 = new Node(value1);
      grafo[value1-1].setValue(value1);
      grafo[value1-1].incrementGrauDeEntrada(1);
      grafo[i].addConexao(&grafo[value1-1]);

      if (value2) {
        // Node* conexao2 = new Node(value2);
        grafo[value2-1].incrementGrauDeEntrada(1);
        grafo[value2-1].setValue(value2);
        grafo[i].addConexao(&grafo[value2-1]);
      }
    }
  }
}

vector<Node*> ordenacaoTopologica(vector<Node>& grafo, unsigned int quantidadeDeNos) {
  vector<Node*> ordemTopologica;
  vector<Node*> filaDeArestasComGrauDeEntradaZero;

  for (unsigned int i = 0; i < quantidadeDeNos; i++)
  {
    if (grafo[i].getGrauEntrada() == 0) {
      filaDeArestasComGrauDeEntradaZero.push_back(&grafo[i]);
    }
  }
  
  // int i = 0;
  while (!filaDeArestasComGrauDeEntradaZero.empty())
  {
    Node* aresta_n = filaDeArestasComGrauDeEntradaZero.back();
    filaDeArestasComGrauDeEntradaZero.pop_back();
    ordemTopologica.push_back(aresta_n);

    for (Node* conexao : aresta_n->getConexoes()) {
      conexao->incrementGrauDeEntrada(-1);

      if (conexao->getGrauEntrada() == 0) {
        filaDeArestasComGrauDeEntradaZero.push_back(conexao);
      }
    }
  }
  

  return ordemTopologica;
}

void printGrafo(const vector<Node>& grafo) {
  for (Node noAtual : grafo) {
    printNode(noAtual);
  }
}

void printNode(const Node& noAtual) {
  cout << noAtual.getValue();

  for (Node* aresta : noAtual.getConexoes()) {
    cout << " -> ";
    cout << aresta->getValue();
  }

  cout << endl;
}
