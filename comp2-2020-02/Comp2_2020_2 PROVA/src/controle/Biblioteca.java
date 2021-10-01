package controle;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import excecao.DevolucaoInvalidaException;
import excecao.LimiteEmprestimosExcedidoException;
import excecao.UsuarioNaoCadastradoException;
import modelo.Livro;
import modelo.Usuario;

public class Biblioteca {
  private HashMap<Long, Usuario> usuarioByCpf = new HashMap<>();
  private HashMap<Long, ArrayList<Livro>> usuarioByLivrosDevidos = new HashMap<>();
  private HashMap<Livro, Integer> livroByQuantidade = new HashMap<>();

  /**
   * quantidade mínima de unidades de um livro que precisam existir nas estantes
   * da biblioteca para que o livro possa ser emprestado
   */
  public static final int MIN_COPIAS_PARA_PODER_EMPRESTAR = 2;

  /**
   * quantidade máxima de livros da biblioteca que podem estar emprestados, a
   * qualquer tempo, a um mesmo usuário
   */
  public static final int MAX_LIVROS_DEVIDOS = 3;

  public Biblioteca() {
    
  }

  /**
   * Cadastra um usuário. Caso o usuário já exista, atualiza seu nome e seu
   * endereço.
   *
   * @param usuario o usuário a ser inserido/atualizado.
   */
  public void cadastrarUsuario(Usuario usuario) {
    this.usuarioByCpf.put(usuario.getCpf(), usuario);
  }

  /**
   * Retorna um usuário previamente cadastrado, a partir do CPF informado.
   *
   * @param cpf o CPF do usuário desejado
   * @return o usuário, caso exista; ou null, caso não exista nenhum usuário
   *         cadastrado com aquele CPF
   */
  public Usuario getUsuario(long cpf) {
    return this.usuarioByCpf.get(cpf);
  }

  /**
   * @return o número total de usuários cadastrados na biblioteca
   */
  public int getTotalDeUsuariosCadastrados() {
    int totalDeUsuarios = 0;

    for (Map.Entry<Long, Usuario> set : usuarioByCpf.entrySet()) {
      totalDeUsuarios++;
    }
    
    return totalDeUsuarios;
  }

  /**
   * Adquire `quantidade` cópias do livro informado e as inclui no acervo da
   * biblioteca.
   *
   * @param livro      o livro sendo adquirido
   * @param quantidade o número de cópias do livro sendo adquiridas
   */
  public void incluirLivroNoAcervo(Livro livro, int quantidade) {
    if (quantidade <= 0) {
      return;
    }

    int quantidadeAtual = this.livroByQuantidade.getOrDefault(livro, 0);
    this.livroByQuantidade.put(livro, quantidadeAtual + quantidade);
  }

  /**
   * Empresta um livro para um usuário da biblioteca.
   *
   * @param livro   o livro a ser emprestado
   * @param usuario o usuário que está pegando emprestado o livro
   *
   * @return true, se o empréstimo foi bem-sucedido; false, se o livro não está
   *         disponível para empréstimo (IMPORTANTE: um livro é considerado
   *         disponível para empréstimo se há pelo menos
   *         controle.Biblioteca.MIN_COPIAS_PARA_PODER_EMPRESTAR cópias daquele
   *         livro nas estantes da biblioteca; isto é, as estantes da biblioteca
   *         jamais poderão ficar com menos do que
   *         controle.Biblioteca.MIN_COPIAS_PARA_PODER_EMPRESTAR-1 cópias de
   *         qualquer livro de seu acervo)
   *
   * @throws UsuarioNaoCadastradoException      se o usuário informado não está
   *                                            cadastrado na biblioteca
   * @throws LimiteEmprestimosExcedidoException se o usuário já está com muitos
   *                                            livros emprestados no momento
   */
  public boolean emprestarLivro(Livro livro, Usuario usuario) throws UsuarioNaoCadastradoException, LimiteEmprestimosExcedidoException {
    if (!this.usuarioCadastrado(usuario)) {
      throw new UsuarioNaoCadastradoException("Usuário não está cadastrado");
    }
    if (this.getQuantidadeDeLivrosDevidos(usuario) >= MAX_LIVROS_DEVIDOS) {
      throw new LimiteEmprestimosExcedidoException("Máximo de livros emprestados");
    }

    int quantidadeDoLivroNoAcervo = this.getQuantidadeDeLivrosNaEstante(livro);

    if (quantidadeDoLivroNoAcervo < MIN_COPIAS_PARA_PODER_EMPRESTAR) {
      return false;
    }

    this.usuarioByLivrosDevidos.computeIfAbsent(usuario.getCpf(), listaDeLivrosDevido -> new ArrayList<>());

    ArrayList<Livro> listaAtualDeLivrosDevidos = this.usuarioByLivrosDevidos.get(usuario.getCpf());
    listaAtualDeLivrosDevidos.add(livro);
    this.usuarioByLivrosDevidos.put(usuario.getCpf(), listaAtualDeLivrosDevidos);

    livroByQuantidade.put(livro, quantidadeDoLivroNoAcervo - 1);
    
    return true;
  }

  /**
   * Verifica se o usuário está cadastrado
   * 
   * @param usuario
   * @return true caso sim, false caso não
   */
  private boolean usuarioCadastrado(Usuario usuario) {
    return this.usuarioByCpf.containsKey(usuario.getCpf());
  }

  /**
   * Recebe de volta um livro que havia sido emprestado.
   *
   * @param livro   o livro sendo devolvido
   * @param usuario o usuário que havia tomado emprestado aquele livro
   *
   * @throws DevolucaoInvalidaException se o livro informado não se encontra
   *                                    emprestado para o usuário informado
   */
  public void receberDevolucaoLivro(Livro livro, Usuario usuario) throws DevolucaoInvalidaException {
    if (!usuarioPossui(livro, usuario)) {
      throw new DevolucaoInvalidaException("Livro informado não se encontra emrpestado para o usuário informado.");
    }

    ArrayList<Livro> listaDeLivrosDevidos = this.usuarioByLivrosDevidos.get(usuario.getCpf());
    listaDeLivrosDevidos.remove(livro);
    this.usuarioByLivrosDevidos.put(usuario.getCpf(), listaDeLivrosDevidos);

    this.livroByQuantidade.put(livro, this.getQuantidadeDeLivrosNaEstante(livro) + 1);
  }

  /**
   * Verifica se o Usuario possui o livro em questão
   * 
   * @param livro
   * @param usuario
   * @return
   */
  private boolean usuarioPossui(Livro livro, Usuario usuario) {
    ArrayList<Livro> listaDeLivrosDevidos = this.usuarioByLivrosDevidos.getOrDefault(usuario.getCpf(), new ArrayList<>());
    
    return listaDeLivrosDevidos.contains(livro);
  }

  /**
   * Retorna a quantidade de livros emprestados ao usuário informado.
   *
   * @param usuario o usuário desejado
   * @return a quantidade de livros emprestados àquele usuário; caso o usuário não
   *         esteja devendo nenhum livro, ou não seja nem mesmo um usuário
   *         cadastrado na biblioteca, retorna zero, não deve nada
   */
  public int getQuantidadeDeLivrosDevidos(Usuario usuario) {
    ArrayList<Livro> listaDeLivrosDevidos = this.usuarioByLivrosDevidos.getOrDefault(usuario.getCpf(), new ArrayList<>());
    
    return listaDeLivrosDevidos.size();
  }

  /**
   * @return a quantidade total de livros nas estantes da biblioteca (isto é, a
   *         soma das quantidades de cópias não-emprestadas de todos os livros do
   *         acervo da biblioteca).
   */
  public int getQuantidadeDeLivrosNaEstante() {
    int totalDeLivros = 0;

    for (Map.Entry<Livro, Integer> set : livroByQuantidade.entrySet()) {
      totalDeLivros += set.getValue();
    }
    
    return totalDeLivros;
  }

  /**
   * Retorna o número de cópias do livro informado que existem na estante da
   * biblioteca (isto é, que não estão emprestados).
   *
   * @param livro o livro desejado
   * @return o número de cópias não-emprestadas daquele livro
   */
  public int getQuantidadeDeLivrosNaEstante(Livro livro) {
    return this.livroByQuantidade.getOrDefault(livro, 0);
  }
}
