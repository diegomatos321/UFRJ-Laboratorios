import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Usuario implements Comparable<Usuario> {
  private int id;
  private Map<Integer, Usuario> amigosById = new HashMap<>();
  private List<Usuario> listaDeAmigos = new ArrayList<>();
  private CalculadorIntersecao calculadorIntersecao;

  public Usuario(int id) {
    // instancia um calculador de interseção
    this.id = id;
  }

  public Usuario(int id, CalculadorIntersecao calculadorIntersecao) {
    this(id);

    this.calculadorIntersecao = calculadorIntersecao;
  }

  public int getId() {
    return id;
  }

  public CalculadorIntersecao getCalculadorIntersecao() {
    return calculadorIntersecao;
  }

  public void setCalculadorIntersecao(CalculadorIntersecao calculadorIntersecao) {
    this.calculadorIntersecao = calculadorIntersecao;
  }

  public List<Usuario> getAmigos() {
    if(this.amigosById.size() != this.listaDeAmigos.size()) {
      this.listaDeAmigos = new ArrayList<Usuario>(this.amigosById.values());
    }

    return this.listaDeAmigos;
  }

  /**
   * Retorna a quantidade de amigos em comum entre este Usuario e o outro Usuario
   * informado.
   *
   * @param outro outro Usuario da rede social
   * @return o tamanho da interseção dos conjuntos de amigos
   */
  public int obterQuantidadeDeAmigosEmComum(Usuario outro) {
    if(calculadorIntersecao == null) return -1;

    return calculadorIntersecao.obterIntersecao(this.getAmigos(), outro.getAmigos()).size();
  }

  /**
   * Adiciona um novo amigo para a lista de amigos do Usuário atual
   * 
   * @param novoAmigo
   */
  public void addAmigo(Usuario novoAmigo) {
    this.amigosById.putIfAbsent(novoAmigo.getId(), novoAmigo);
  }

  @Override
  public int compareTo(Usuario o) {
    return this.id - o.id;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (obj == null)
      return false;
    if (getClass() != obj.getClass())
      return false;
    Usuario other = (Usuario) obj;
    if (id != other.id)
      return false;
    return true;
  }
}
