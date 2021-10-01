import org.junit.Before;
import org.junit.Test;

import java.awt.*;
import java.awt.image.BufferedImage;

import static org.junit.Assert.*;

public class TuiterLiteTest {

  private TuiterLite tuiterLite;
  private Usuario usuario;

  @Before
  public void setUp() throws UsuarioJaExisteException {
    tuiterLite = new TuiterLite();

    this.usuario = tuiterLite.cadastrarUsuario("Fulano", "fulano@teste.com");

    Image foto = new BufferedImage(100, 100, BufferedImage.TYPE_INT_RGB);
    this.usuario.setFoto(foto);
  }

  @Test
  public void testeUsuariosReconhecidosCorretamente() {
    assertEquals("Duas instâncias de Usuario devem ser consideradas iguais se possuirem o mesmo email", this.usuario,
        new Usuario("Fulano de Tal", "fulano@teste.com"));
  }

  @Test
  public void testeAutorDoTuite() throws TamanhoMaximoExcedidoException, UsuarioDesconhecidoException {
    Tuite tuite = tuiterLite.tuitarAlgo(this.usuario, "Testando");
    assertEquals("O tuíte deve retornar corretamente seu autor", this.usuario, tuite.getAutor());
  }

  @Test
  public void testeTamanhoTuite() throws UsuarioDesconhecidoException {
    for (int excessoCaracteres = 1; excessoCaracteres <= 100; excessoCaracteres++) {
      int tamanho = TuiterLite.TAMANHO_MAXIMO_TUITES + 1;
      StringBuilder sb = new StringBuilder();

      for (int i = 1; i <= tamanho; i++) {
        sb.append("x");
      }

      String texto = sb.toString();
      assertNull("Não deve ser possível tuitar algocom otamanho maior do que " + "o máximo permitido",
          tuiterLite.tuitarAlgo(usuario, texto));
    }
  }

  @Test
  @SuppressWarnings("unchecked")
  public void testeAnexo() throws TamanhoMaximoExcedidoException, UsuarioDesconhecidoException {

    Tuite tuite = tuiterLite.tuitarAlgo(usuario, "Testando");

    tuite.anexarAlgo(usuario.getFoto());
    assertEquals("O tuíte deve retornar corretamente o objeto que foi anexado a ele", usuario.getFoto(),
        tuite.getAnexo());

    Object objeto = new Object();
    tuite.anexarAlgo(objeto);
    assertEquals("O tuíte deve sobrescrever o anexo anterior (se existir) com o novo anexo", objeto, tuite.getAnexo());
  }

  @Test
  public void testeHashtags() throws TamanhoMaximoExcedidoException, UsuarioDesconhecidoException {

    Tuite tuite = tuiterLite.tuitarAlgo(usuario, "#LAB7 Testando algo com #hashtag ao longo... #teste");

    assertTrue("Hashtags devem ser detectadas automaticamente e adicionadas ao tuíte",
        tuite.getHashtags().contains("#hashtag"));
    assertTrue("Hashtags devem ser detectadas automaticamente inclusive no começo do tuíte",
        tuite.getHashtags().contains("#LAB7"));
    assertTrue("Hashtags devem ser detectadas automaticamente inclusive no fim do tuite",
        tuite.getHashtags().contains("#teste"));

    assertFalse(tuite.getHashtags().contains("#algo"));
    assertFalse(tuite.getHashtags().contains("algo"));
    assertFalse(tuite.getHashtags().contains("#paralelepipedo"));

    tuiterLite.tuitarAlgo(usuario, "Repetindo o uso de uma hashtag #LAB7");
    assertEquals("Hashtags devem ser contabilizadas corretamente pelo sistema", "#LAB7",
        tuiterLite.getHashtagMaisComum());
  }
}