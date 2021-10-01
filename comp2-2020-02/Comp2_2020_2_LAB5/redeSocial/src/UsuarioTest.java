import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class UsuarioTest {
  private static final int QUANTIDADE_DE_AMIGOS = 100;
  private static final int QUANTIDADE_DE_USUARIOS = 1_000;
  private List<Usuario> listaDeUsuarios = new ArrayList<Usuario>();

  /**
   * Antes de todo teste iremos alocar memória para os usuários assim como sortear os amigos que eles terão
   */
  @Before
  public void setUp() {
    final Random sorteio = new Random();

    for (int i = 0; i < QUANTIDADE_DE_USUARIOS; i++) {
      this.listaDeUsuarios.add(new Usuario(i));
    }

    for (int i = 0; i < QUANTIDADE_DE_USUARIOS; i++) {
      final Usuario usuarioAtual = this.listaDeUsuarios.get(i);
      final List<Usuario> listaDeAmigos = usuarioAtual.getAmigos();

      for (int j = 0; j < QUANTIDADE_DE_AMIGOS; j++) {
        Usuario amigoSorteado;
        int indiceSorteado;

        do {
          indiceSorteado = sorteio.nextInt(QUANTIDADE_DE_USUARIOS);
          amigoSorteado = this.listaDeUsuarios.get(indiceSorteado);
        } while (indiceSorteado == i || listaDeAmigos.contains(amigoSorteado) == true);

        usuarioAtual.addAmigo(amigoSorteado);
      }
    }
  }

  /**
   * Testaremos as performances de algoritmos distintos que calculam a quantidade de amigos em comum
   * que os usuários possuem entre si
   */
  @Test
  public void testarPerformance() {
    long inicio = System.currentTimeMillis();
    System.out.println("Teste do Calculador Ingênuo com " + QUANTIDADE_DE_USUARIOS + " Usuários...");
    testarCalculadorIngenuo(false);
    System.out.println("Teste finalizado");
    long duracao = System.currentTimeMillis() - inicio;
    System.out.println("Duração = " + duracao + "ms");
    
    inicio = System.currentTimeMillis();
    System.out.println("Teste do Calculador Esperto com " + QUANTIDADE_DE_USUARIOS + " Usuários...");
    testarCalculadorIntersecaoEsperto(false);
    System.out.println("Teste finalizado");
    duracao = System.currentTimeMillis() - inicio;
    System.out.println("Duração = " + duracao + "ms");

    inicio = System.currentTimeMillis();
    System.out.println("Teste do Calculador Via Busca Binaria com " + QUANTIDADE_DE_USUARIOS + " Usuários...");
    testarCalculadorIntersecaoViaBuscaBinaria(false);
    System.out.println("Teste finalizado");
    duracao = System.currentTimeMillis() - inicio;
    System.out.println("Duração = " + duracao + "ms");
  }

  /**
   * Responsável por instanciar o calculador em questão
   * @param showOutput true para mostrar, individualmente, a quantidade de amigos em comum com cada usuário,
   * e false, para não mostrar
   */
  public void testarCalculadorIngenuo(boolean showOutput) {
    final CalculadorIntersecaoIngenuo calculadorIngenuo = new CalculadorIntersecaoIngenuo();

    this.definirCalculadorETestarAsIntersecoes(calculadorIngenuo, showOutput);
  }

  public void testarCalculadorIntersecaoEsperto(boolean showOutput) {
    final CalculadorIntersecaoEsperto calculadorEsperto = new CalculadorIntersecaoEsperto();

    definirCalculadorETestarAsIntersecoes(calculadorEsperto, showOutput);
  }

  public void testarCalculadorIntersecaoViaBuscaBinaria(boolean showOutput) {
    final CalculadorIntersecaoViaBuscaBinaria calculadorBinario = new CalculadorIntersecaoViaBuscaBinaria();

    definirCalculadorETestarAsIntersecoes(calculadorBinario, showOutput);
  }

  /**
   * Responsável por definir o calculador em questão para TODOS os usuários e, em seguida, 
   * executar o calculador.
   * @param calculador
   * @param showOutput
   */
  private void definirCalculadorETestarAsIntersecoes(CalculadorIntersecao calculador, boolean showOutput) {
    StringBuilder sb = null;

    if(showOutput == true) {
      sb = new StringBuilder();
    }

    for (int i = 0; i < QUANTIDADE_DE_USUARIOS; i++) {
      this.listaDeUsuarios.get(i).setCalculadorIntersecao(calculador);
    }

    for (int i = 0; i < QUANTIDADE_DE_USUARIOS; i++) {
      final Usuario usuarioAtual = this.listaDeUsuarios.get(i);
      int quantidadeDeAmigosEmComum = 0;

      for (int j = i + 1; j < QUANTIDADE_DE_USUARIOS; j++) {
        final Usuario outroUsuario = this.listaDeUsuarios.get(j);
        
        quantidadeDeAmigosEmComum = usuarioAtual.obterQuantidadeDeAmigosEmComum(outroUsuario);
        
        if(showOutput == true) {
          sb.setLength(0);
          sb.append("Fulano ").append(usuarioAtual.getId()).append(" possui ").append(quantidadeDeAmigosEmComum)
              .append(" amigos em comum com Ciclano ").append(outroUsuario.getId());
          System.out.println(sb.toString());
        }
      }
    }
  }
}
