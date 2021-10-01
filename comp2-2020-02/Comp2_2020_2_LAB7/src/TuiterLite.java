import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;

/**
 * Esta classe implementa um sistema de mensagens curtas estilo Twitter. É
 * preciso cadastrar um usuário, identificado pelo seu e-mail, para que tuítes
 * possam ser feitos. Usuários começam como iniciantes, depois são promovidos a
 * senior e a ninja, em função do número de tuítes. Existe um tamanho máximo
 * permitido por mensagem (constante TAMANHO_MAXIMO_CARACTERES). As mensagens
 * podem conter hashtags (palavras iniciadas por #), que são detectadas
 * automaticamente. Os tuítes podem conter, além da mensagem de texto, um anexo
 * qualquer. Há um método para retornar, a qualquer momento, qual a hashtag mais
 * usada em toda a história do sistema.
 */
public class TuiterLite {
  public static final int TAMANHO_MAXIMO_TUITES = 120;

  private HashSet<Usuario> usuariosCadastrados = new HashSet<>();
  private HashMap<Usuario, Tuite> tuiteByUsuario = new HashMap<>();
  private HashMap<String, Integer> quantidadeByHashtag = new HashMap<>();

  /**
   * Cadastra um usuário, retornando o novo objeto Usuario criado.
   * 
   * @param nome  O nome do usuário.
   * @param email O e-mail do usuário (precisa ser único no sistema).
   * @return O Usuario criado.
   */
  public Usuario cadastrarUsuario(String nome, String email) { // throws UsuarioJaExisteException {
    Usuario novoUsuario = new Usuario(nome, email);

    usuariosCadastrados.add(novoUsuario);

    return novoUsuario;
  }

  /**
   *
   * @param usuario O autor do tuíte
   * @param texto   O texto desejado
   * @return Um "tuíte", que será devidamente publicado no sistema
   *
   *         PS.: Se o texto exceder o limite pré-definido, ou o usuário não
   *         estiver cadastrado, return null
   */
  public Tuite tuitarAlgo(Usuario usuario, String texto) {
    if (usuarioECadastrado(usuario) == false || texto.length() > TAMANHO_MAXIMO_TUITES) {
      return null;
    }

    List<String> listaDeHashtags = new ArrayList<>();
    for (String palavra : texto.split(" ")) {
      if (palavra.charAt(0) == '#') {
        String hashtag = "#" + palavra.replaceAll("#", "");
        listaDeHashtags.add(hashtag);

        int quantidadeDeHahstag = quantidadeByHashtag.getOrDefault(hashtag, 0);
        quantidadeByHashtag.put(hashtag, quantidadeDeHahstag + 1);
      }
    }

    Tuite novoTuite = new Tuite(usuario, texto, listaDeHashtags);
    tuiteByUsuario.put(usuario, novoTuite);

    return novoTuite;
  }

  private boolean usuarioECadastrado(Usuario usuario) {
    return usuariosCadastrados.contains(usuario);
  }

  /**
   * Retorna a hashtag mais comum dentre todas as que já apareceram. A cada tuíte
   * criado, hashtags devem ser detectadas automaticamente para que este método
   * possa funcionar.
   * 
   * @return A hashtag mais comum, ou null se nunca uma hashtag houver sido
   *         tuitada.
   */
  public String getHashtagMaisComum() {
    String hashtagMaisComum = null;
    int quantidadeDeHashtag = 0;

    for (Map.Entry<String, Integer> par : quantidadeByHashtag.entrySet()) {
      String hashtag = par.getKey();
      Integer quantidade = par.getValue();

      if (hashtagMaisComum == null || quantidade > quantidadeDeHashtag) {
        hashtagMaisComum = hashtag;
        quantidadeDeHashtag = quantidade;
      }
    }

    return hashtagMaisComum;
  }
}
