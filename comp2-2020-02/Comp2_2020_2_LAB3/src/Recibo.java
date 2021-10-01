import java.text.DecimalFormat;

public class Recibo {

  private Usuario comprador;
  private Produto produtoComprado;
  private int quantidadeComprada;
  private float valorTotalDaCompra;
  
  public Recibo(Usuario comprador, Produto produtoComprado, int quantidadeComprada) {
    this.comprador = comprador;
    this.produtoComprado = produtoComprado;
    this.quantidadeComprada = quantidadeComprada;
    this.valorTotalDaCompra = produtoComprado.getPreco() * quantidadeComprada;
  }

  public Usuario getComprador() {
    return comprador;
  }

  public Produto getProdutoComprado() {
    return produtoComprado;
  }

  public int getQuantidadeComprada() {
    return quantidadeComprada;
  }

  public float getValorTotalDaCompra() {
    return valorTotalDaCompra;
  }

  public Usuario getUsuario() {
    return comprador;
  }

  @Override
  public String toString() {
    String formato = "R$ #,##0.00";
    DecimalFormat df = new DecimalFormat(formato);
    String preco = df.format(this.getValorTotalDaCompra());
    
    final String texto = "Recibo no valor de " + preco + " para " + this.comprador.getNome() + " referente à compra de " + this.quantidadeComprada + " unidades de " + this.produtoComprado.toString();

    return texto;
  }
}
