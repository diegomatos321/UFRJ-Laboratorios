import java.awt.Image;

public class Item {
  private final int posicao;
  private String rotaDoItem;
  protected String urlDaImagem;

  public Item(int posicao, String rotaDoItem) {
    this.posicao = posicao;
    this.rotaDoItem = rotaDoItem;
    this.urlDaImagem = rotaDoItem;
  }

  public String getRotaDoItem() {
    return rotaDoItem;
  }

  public String getUrlDaImagem() {
    return urlDaImagem;
  }

  public void setUrlDaImagem(String urlDaImagem) {
    this.urlDaImagem = urlDaImagem;
  }

  public int getPosicao() {
    return this.posicao;
  }

  protected Image obterImagem(String url) {
    // ToDo baixaria da Internet...
    return null;
  }
}
