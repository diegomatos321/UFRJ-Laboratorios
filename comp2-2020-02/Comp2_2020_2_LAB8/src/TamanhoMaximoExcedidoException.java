public class TamanhoMaximoExcedidoException extends Exception {
  private int tamanhoExcedido;

  public TamanhoMaximoExcedidoException(String message) {
    super(message);
  }

  public TamanhoMaximoExcedidoException(String message, int tamanhoExcedido) {
    super(message);

    this.tamanhoExcedido = tamanhoExcedido;
  }

  public int getTamanhoExcedido() {
    return tamanhoExcedido;
  }
}
