import java.util.*;

public class Primos {
  public static final int riscado = 0;
  public static final int aberto = 1;

  public static void main(String[] args) throws Exception {
    List<Integer> listaDeNumerosPrimos = new ArrayList<Integer>();
    long inicio = 0, tempoDeExecucao = 0;

    System.out.println("=== Usando Crivo de Erastostenes ===");
    for (int i = 10; i < 100_000_000; i*=10) {
      inicio = System.currentTimeMillis();
      listaDeNumerosPrimos = crivoDeEratostenes(i);
      tempoDeExecucao = System.currentTimeMillis() - inicio;

      System.out.printf("Duração: %.9f\n", tempoDeExecucao/1000.0);
      System.out.println("Há " + listaDeNumerosPrimos.size() + " números primos no intervalo [ 1, " + i + " ].");  
    }

    System.out.println("=== Sem o Crivo ===");
    for (int i = 10; i < 100_000_000; i*=10) {
      inicio = System.currentTimeMillis();
      listaDeNumerosPrimos = listaDeNumerosPrimos(i);
      tempoDeExecucao = System.currentTimeMillis() - inicio;

      System.out.printf("Duração: %.9f\n", tempoDeExecucao/1000.0);
      System.out.println("Há " + listaDeNumerosPrimos.size() + " números primos no intervalo [ 1, " + i + " ].");  
    }
  }

  public static List<Integer> crivoDeEratostenes(int n) {
    int[] crivo = new int[(n-1)/2];
    List<Integer> primos = new ArrayList<Integer>();

    primos.add(2); /* Único primo Par */

    for (int i = 0; i < crivo.length; i++) {
      crivo[i] = aberto;
    }

    for (int P = 3; P <= (int) Math.sqrt(n); P += 2) {
      int valorNoCrivo = crivo[(P-1)/2];

      if (valorNoCrivo == riscado) {
        continue;
      }

      for (int T = P * P; T < n; T += 2 * P) {
        int posicao = (T-1)/2;

        if(posicao == crivo.length) break;

        crivo[posicao] = riscado;
      }
    }

    for (int i = 1; i < crivo.length; i++) {
      int valorNoCrivo = crivo[i];

      if (valorNoCrivo == aberto) {
        int primoReal = 2 * i + 1;
        primos.add(primoReal);
      }
    }

    return primos;
  }

  public static List<Integer> listaDeNumerosPrimos(int n) {
    List<Integer> primos = new ArrayList<Integer>();
    
    for (int P = 2; P < n; P++) {
      if(forNumeroPrimo(P)) {
        primos.add(P);
      }
    }

    return primos;
  }

  public static boolean forNumeroPrimo(int n) {
    boolean isPrimo = false, possuiFator = false;

    for (int F = 2; F <= (int) Math.sqrt(n); F++) {
      if (n % F == 0) {
        possuiFator = true;
        break;
      }
    }

    if(possuiFator == false) {
      isPrimo = true;
    }

    return isPrimo;
  }
}
