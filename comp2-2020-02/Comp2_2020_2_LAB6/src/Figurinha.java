import java.awt.Image;

public class Figurinha extends Item implements IColecionavel{
  private final Image imagem;

  public Figurinha(int posicao, String rotaDaImagem) {
    super(posicao, rotaDaImagem);

    this.imagem = this.obterImagem(this.urlDaImagem);
  }
  
  public Image getImagem() {
    return imagem;
  }
}
