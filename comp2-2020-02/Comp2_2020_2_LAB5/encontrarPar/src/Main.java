import java.util.Arrays;
import java.util.Random;

public class Main {
  static final int QUANTIDADE_DE_INTEIROS = 1_000;
  static final int k = 5632;
  static final int VALOR_MAXIMO = 75;

  /**
   * Instancia uma lista de inteiros previamente definos e executa um algoritmo para encontrar
   * um par de inteiros que somados sejam iguais à k.
   * @param args
   */
  public static void main(String[] args) {
    int[] lista = new int[QUANTIDADE_DE_INTEIROS];
    Random rand = new Random();

    for (int i = 1; i < QUANTIDADE_DE_INTEIROS; i++) {
      lista[i] = i * rand.nextInt(VALOR_MAXIMO);
    }

    System.out.println("Testando encontrar Par");
    long inicio = System.currentTimeMillis();
    int[] par = encontrarPar(lista, k);
    long duracao = System.currentTimeMillis() - inicio;
    System.out.println("Par = " + Arrays.toString(par));
    System.out.println("Teste finalizando. Duração = " + duracao);
  }

  /**
   * Realiza uma busca dentro de uma lista com n inteiros para encontrar dois números que SOMADOS são iguais à k.
   * Como a + b = k, no primeiro passo iteremos pela lista e encontramos um inteiro que chamaremos de a, logo, b = k - a. 
   * Então, no segundo passo, procuramos na lista um inteiro que satisfaz k - a começando por i, pois, o algoritmo
   * já teria terminado caso um numero anterior satisfizesse a condição.
   * @param lista Conjunto de números
   * @param k Soma esperado entre dois números dentro do conjunto
   * @return Retorna um único par de números dentro do conjunto fornecido que satisfaz k
   */
  private static int[] encontrarPar(int[] lista, int k) {
    int[] par = {0, 0};

    for (int i = 0; i < lista.length; i++) {
      final int a = lista[i];
      final int numeroAEncontrar = k - a;

      for (int j = i; j < lista.length; j++) {
        final int b = lista[j];

        if (b == numeroAEncontrar) {
          par[0] = a;
          par[1] = b;
          return par;
        }
      }
    }

    return par;
  }
}
