import java.util.HashMap;
import java.util.Map;

public class Repositorio<Colecionavel extends Item & IColecionavel> {
  private static final String PREFIXO_URL_IMAGENS = "http://www.nossoalbum.com.br/imagens/";
  private final String SUFIXO_URL_IMAGENS;

  private final int TAMANHO_MAXIMO;
  private Map<Integer, Colecionavel> colecionavelByPosicao = new HashMap<>();
  private int quantidadeDeColecionaveis = 0;

  public Repositorio(String sufixoUrlImagens, int TAMANHO_MAXIMO) {
    this.TAMANHO_MAXIMO = TAMANHO_MAXIMO;
    this.SUFIXO_URL_IMAGENS = sufixoUrlImagens;
  }

  public void addToRepositorio(Colecionavel colecionavel) {
    if (quantidadeDeColecionaveis >= TAMANHO_MAXIMO) {
      return;
    }

    StringBuilder sb = new StringBuilder();

    sb.append(PREFIXO_URL_IMAGENS).append(SUFIXO_URL_IMAGENS).append(colecionavel.getRotaDoItem());
    colecionavel.setUrlDaImagem(sb.toString());

    colecionavelByPosicao.put(colecionavel.getPosicao(), colecionavel);
    quantidadeDeColecionaveis++;
  }

  public final int getQuantidadeDeColecionaveis() {
    return this.quantidadeDeColecionaveis;
  }

  public final int getTamanhoMaximo() {
    return this.TAMANHO_MAXIMO;
  }

  public Colecionavel getColecionavel(int posicao) {
    return colecionavelByPosicao.get(posicao);
  }
}
