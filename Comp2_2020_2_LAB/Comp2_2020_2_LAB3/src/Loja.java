import java.util.*;

/**
 * Implementa uma loja virtual para produtos de qualquer tipo, desde que tenham
 * descrição, preço e dimensões.
 *
 * Essa classe será um singleton, isto é, permitiremos apenas uma instância
 * desde objeto no sistema.
 */
public class Loja {

  private static final Loja instanciaUnica = new Loja();

  private List<Usuario> usuarios = new ArrayList<Usuario>();
  private List<Produto> produtosCadastrados = new ArrayList<Produto>();
  private Map<String, Integer> estoque = new HashMap<String, Integer>();

  public static Loja getInstanciaUnica() {
    return instanciaUnica;
  }

  /**
   * Inclui no estoque da loja a quantidade informado do produto.
   *
   * @param produto            o produto a ser incluído
   * @param quantidadeAIncluir a quantidade que será acrescentada à quantidade
   *                           existente.
   */
  public void incluirProduto(Produto produto, int quantidadeAIncluir) {
    if (quantidadeAIncluir <= 0)
      return;

    if (!produtoExiste(produto)) {
      produtosCadastrados.add(produto);
      estoque.put(produto.toString(), quantidadeAIncluir);

      return;
    }

    estoque.put(produto.toString(), this.estoque.get(produto.toString()) + quantidadeAIncluir);
  }

  public void cadastrarUsuario(Usuario usuario) {
    this.usuarios.add(usuario);
  }

  /**
   * Efetua a venda do produto desejado na quantidade especificada.
   *
   * @param produto            o produto
   * @param quantidadeDesejada a quantidade
   * @param usuario            cliente da compra
   *
   * @return um Recibo indicando a venda feita, se o produto existia (em
   *         quantidade suficiente) no estoque da loja; null, caso o usuário ou o
   *         produto sejam desconhecidos, ou não haja quantidade suficiente do
   *         produto desejado
   */
  public Recibo efetuarVenda(Produto produto, int quantidadeDesejada, Usuario usuario) {
    if (!usuarioExiste(usuario) || !produtoExiste(produto) || quantidadeDesejada <= 0
        || this.estoque.get(produto.toString()) <= 0) {
      return null;
    }

    Integer quantidadeRetirada = this.retirarDoEstoque(produto, quantidadeDesejada);

    if (quantidadeRetirada == quantidadeDesejada) {
      Recibo reciboDeVenda = new Recibo(usuario, produto, quantidadeDesejada);

      return reciboDeVenda;
    }

    return null;
  }

  /**
   * Retira do estoque da loja a quantidade informada do produto, caso seja
   * possível.
   *
   * @param produto            o produto a ser incluído
   * @param quantidadeARetirar a quantidade que será retirada do estoque
   *                           existente.
   * 
   * @return A quantidade de items retirados com êxito ou caso não seja possível
   *         retirar todos: quantidade de items existentes no estoque ou null
   *         para caso o produto não exista.
   */
  private Integer retirarDoEstoque(Produto produto, int quantidadeARetirar) {
    if (!produtoExiste(produto) || quantidadeARetirar <= 0) {
      return null;
    }

    Integer quantidadeAtual = this.estoque.get(produto.toString());

    if (quantidadeAtual - quantidadeARetirar < 0) {
      return quantidadeAtual;
    }

    estoque.put(produto.toString(), quantidadeAtual - quantidadeARetirar);

    return quantidadeARetirar;
  }

  private boolean usuarioExiste(Usuario usuario) {
    return usuarios.contains(usuario);
  }

  private boolean produtoExiste(Produto produto) {
    return produtosCadastrados.contains(produto);
  }

  /**
   * @param produto o produto a ser consultado
   *
   * @return a quantidade em estoque; 0 se não houver nenhuma unidade; -1 se o
   *         produto não é sequer vendido pela loja
   */
  public int informarQuantidadeEmEstoque(Produto produto) {
    int quantidadeEmEstoque = estoque.get(produto.toString());

    return quantidadeEmEstoque;
  }
}
