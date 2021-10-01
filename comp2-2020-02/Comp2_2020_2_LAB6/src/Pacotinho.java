import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Pacotinho<Colecionavel extends Item & IColecionavel> {
  private final Repositorio<Colecionavel> repositorioDeColecionaveis;
  private final List<Colecionavel> colecionaveisNoPacote = new ArrayList<>();

  public Pacotinho(Repositorio<Colecionavel> repo, int[] posicoesDesejadas) {
    this.repositorioDeColecionaveis = repo;

    for (int posicao : posicoesDesejadas) {
      colecionaveisNoPacote.add(repo.getColecionavel(posicao));
    }
  }

  /**
   * Produz um pacotinho com quantColecionaveis sorteadas aleatoriamente dentre
   * aqueles presentes no repositório informado.
   *
   * @param repo            o repositório desejado
   * @param quantColecionaveis a quantidade de colecionaveis a constar no pacotinho
   */
  public Pacotinho(Repositorio<Colecionavel> repo, int quantColecionaveis) {
    this.repositorioDeColecionaveis = repo;
    Random rand = new Random();

    for (int i = 0; i < quantColecionaveis; i++) {
      int posicaoAleatoria = rand.nextInt(repo.getTamanhoMaximo() - 1) + 1;

      colecionaveisNoPacote.add(repo.getColecionavel(posicaoAleatoria));
    }
  }

  public Repositorio<Colecionavel> getRepositorioDeColecionaveis() {
    return this.repositorioDeColecionaveis;
  }

  public List<Colecionavel> getColecionaveisNoPacote() {
    return this.colecionaveisNoPacote;
  }
}
