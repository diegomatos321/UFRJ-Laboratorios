import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class CalculadorIntersecaoViaBuscaBinaria implements CalculadorIntersecao {

  @Override
  public List<Usuario> obterIntersecao(List<Usuario> lista1, List<Usuario> lista2) {

    List<Usuario> intersecao = new ArrayList<>();

    Collections.sort(lista1);

    for (Usuario usuarioDaSegundaLista : lista2) {
      if (Collections.binarySearch(lista1, usuarioDaSegundaLista) >= 0) {
        // a busca binária encontrou o elemento
        intersecao.add(usuarioDaSegundaLista);
      }
    }

    return intersecao;
  }
}
