import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class Main {
  /* Caso queriamos considerar apenas letras do nosso alfabeto, usar o regexp abaixo */
  /* static final String excecoes = "[\s+\\d+\t+\n+\r+$-/:-?{-~!^_`]"; */

  /* Caso queira desconsiderar apenas os espaços/tabs/quebras de linha, considerar o regexp abaixo */
  static final String excecoes = "[\s+\t+\n+\r+]";

  public static void main(String[] args) {
    String palavra = "O Tom é um bom menino !"; /* Tom é o meu cachorro :D */

    char[] caracterMaisFrequente = encontrarCaracterMaisFrequente(palavra);

    System.out.println(Arrays.toString(caracterMaisFrequente));
  }

  private static char[] encontrarCaracterMaisFrequente(String palavra) {
    char[] caracterMaisFrequente = new char[2];
    Map<Character, Integer> frequenciaByCharacter = new HashMap<>();

    String palavraNormalizada = filtro(palavra);

    for (int i = 0; i < palavraNormalizada.length(); i++) {
      char character = palavraNormalizada.charAt(i);

      frequenciaByCharacter.putIfAbsent(character, 0);
      frequenciaByCharacter.put(character, frequenciaByCharacter.get(character) + 1);
    }

    for (Map.Entry<Character, Integer> par : frequenciaByCharacter.entrySet()) {
      Character character = par.getKey();
      Integer frequencia = par.getValue();

      char maiorCharacterAtual = caracterMaisFrequente[0];
      int maiorFrequenciaAtual = Character.getNumericValue(caracterMaisFrequente[1]);

      if (maiorCharacterAtual == ' ' || frequencia > maiorFrequenciaAtual) {
        caracterMaisFrequente[0] = character;
        caracterMaisFrequente[1] = Character.forDigit(frequencia, 10);
      }
    }

    return caracterMaisFrequente;
  }

  private static String filtro(String palavra) {
    return palavra.replaceAll(excecoes, "");
  }
}
