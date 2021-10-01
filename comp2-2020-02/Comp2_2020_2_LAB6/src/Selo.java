import java.awt.Image;

public class Selo extends Item implements IColecionavel{
  private String pais;
  private float valorNominal;
  private Image imagem;

  public Selo(int posicao, String rotaDoSelo) {
    super(posicao, rotaDoSelo);

    this.imagem = this.obterImagem(this.urlDaImagem);
  }
  
  public Selo(int posicao, String urlDaImagem, String pais, float valorNominal) {
    this(posicao, urlDaImagem);

    this.pais = pais;
    this.valorNominal = valorNominal;
  }

  public float getValorNominal() {
    return valorNominal;
  }

  public String getPais() {
    return pais;
  }

  public Image getImagem() {
    return imagem;
  }
}
