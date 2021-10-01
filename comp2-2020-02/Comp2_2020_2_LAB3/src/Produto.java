/**
 * O produto precisa ser instanciado com, pelo menos, um nome, a descrição, o preco e as
 * dimensões. Assim como foi definido pela classe Loja.
 */
public class Produto {

  protected String nome;
  protected String descricao;
  protected float preco;
  protected Dimensoes dimensoes;
  protected String urlDaImagem;

  public Produto(String nome, String descricao, float preco, Dimensoes dimensoes) {
    this.nome = nome;
    this.descricao = descricao;
    this.preco = preco;
    this.dimensoes = dimensoes;
  }

  public String getNome() {
    return nome;
  }

  public float getPreco() {
    return preco;
  }

  public void setPreco(float preco) {
    this.preco = preco;
  }

  /**
   * @return uma descrição textual do produto
   */
  public String getDescricao() {
    return this.descricao;
  }

  public void setDescricao(String descricao) {
    this.descricao = descricao;
  }

  public int getPesoEmGramas() {
    return this.dimensoes.getPesoEmGramas();
  }

  public Dimensoes getDimensoes() {
    return this.dimensoes;
  }

  public float precoEmReais() {
    return this.preco;
  }

  public void setPrecoEmReais(float novoPreco) {
    this.preco = novoPreco;
  }

  public String getUrlDaImagem() {
    return this.urlDaImagem;
  }

  public void setUrlDaImagem(String urlDaImagem) {
    this.urlDaImagem = urlDaImagem;
  }

  public void setDimensoes(Dimensoes dimensoes) {
    this.dimensoes = dimensoes;
  }

  @Override
  public String toString() {
    return this.getClass().getName() + ": " + this.getNome();
  }
}
