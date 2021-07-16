public class Brinquedo extends Produto {

  private String marca;
  private int idadeMinimaRecomendada;
  
  public Brinquedo(String nome, String descricao, float preco, Dimensoes dimensoes) {
    super(nome, descricao, preco, dimensoes);
  }

  public String getMarca() {
    return this.marca;
  }
  
  public void setMarca(String marca) {
    this.marca = marca;
  }

  public int getIdadeMinimaRecomendada() {
    return this.idadeMinimaRecomendada;
  }

  public void setIdadeMinimaRecomendada(int idadeMinimaRecomendada) {
    this.idadeMinimaRecomendada = idadeMinimaRecomendada;
  }
}
