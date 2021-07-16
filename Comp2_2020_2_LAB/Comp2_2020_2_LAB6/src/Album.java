import java.awt.Image;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Album<Colecionavel extends Item & IColecionavel> {
  public static final int PERCENTUAL_MINIMO_PARA_AUTO_COMPLETAR = 90;
  public static final Image IMAGEM_PADRAO_PARA_POSICAO_VAZIA = null;

  private final Repositorio<Colecionavel> repositorio;
  private final int quantColecionaveisPorPacotinho;

  private List<Colecionavel> colecionaveisColadas;
  private int quantColecionaveisColadas;
  private Map<Integer, Integer> contRepetidasByPosicao = new HashMap<>();

  public Album(Repositorio<Colecionavel> repositorio, int quantColecionaveisPorPacotinho) {
    this.repositorio = repositorio;
    this.quantColecionaveisPorPacotinho = quantColecionaveisPorPacotinho;

    int tamanhoFisicoDaLista = this.getTamanho() + 1;
    this.colecionaveisColadas = new ArrayList<>(tamanhoFisicoDaLista);

    for (int i = 1; i <= tamanhoFisicoDaLista; i++) {
      this.colecionaveisColadas.add(null);
    }
    
    this.quantColecionaveisColadas = 0;
  }

  public void receberNovoPacotinho(Pacotinho<Colecionavel> pacotinho) {
    List<Colecionavel> colecionaveisNoPacotinho = pacotinho.getColecionaveisNoPacote();
    
    if (colecionaveisNoPacotinho.size() != this.quantColecionaveisPorPacotinho) {
      return; // melhor ainda: lançaria uma checked exception
    }

    for (Colecionavel colecionavel : colecionaveisNoPacotinho) {
      final int posicao = colecionavel.getPosicao();

      if (possuiItemColado(posicao)) {
        this.addColecionavelRepetida(colecionavel);
      } else {
        this.addNovoColecionavel(colecionavel);
      }
    }
  }

  private void addNovoColecionavel(Colecionavel colecionavel) {
    final int posicao = colecionavel.getPosicao();

    this.colecionaveisColadas.set(posicao, colecionavel);
    this.contRepetidasByPosicao.put(posicao, 0);
    this.quantColecionaveisColadas++;
  }

  private void addColecionavelRepetida(Colecionavel colecionavel) {
    final int posicao = colecionavel.getPosicao();

    int contRepetidas = this.contRepetidasByPosicao.getOrDefault(posicao, 0);
    this.contRepetidasByPosicao.put(posicao, contRepetidas + 1);
  }

  public Colecionavel getItemColado(int posicao) {
    return colecionaveisColadas.get(posicao);
  }

  public boolean possuiItemColado(int posicao) {
    if (posicao <= 0 || posicao > this.getTamanho()) {
      return false;
    }

    return colecionaveisColadas.get(posicao) != null;
  }

  public boolean possuiItemRepetido(int posicao) {
    int quantColecionaveis = this.contRepetidasByPosicao.get(posicao);
    return quantColecionaveis >= 1;
  }

  public int getTamanho() {
    return this.repositorio.getTamanhoMaximo();
  }

  public int getQuantItensColados() {
    return this.quantColecionaveisColadas;
  }

  public int getQuantItensFaltantes() {
    return this.getTamanho() - this.getQuantItensColados();
  }

  public void autoCompletar() {
    int minimoColecionaveisColadasParaAutoCompletar = this.repositorio.getTamanhoMaximo() * PERCENTUAL_MINIMO_PARA_AUTO_COMPLETAR / 100;

    if(this.getQuantItensColados() <= 0 || this.quantColecionaveisColadas < minimoColecionaveisColadasParaAutoCompletar) {
      return;
    }

    for (int i = 1; i <= this.repositorio.getTamanhoMaximo(); i++) {
      if(this.possuiItemColado(i) == false) {
        final Colecionavel colecionavel = this.repositorio.getColecionavel(i);
        this.addNovoColecionavel(colecionavel);
      } 
    }
  }

  private Image getImagem(int posicao) {
    return possuiItemColado(posicao) ? this.getItemColado(posicao).getImagem() : IMAGEM_PADRAO_PARA_POSICAO_VAZIA;
  }
}
