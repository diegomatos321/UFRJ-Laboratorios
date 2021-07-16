import org.junit.Before;
import org.junit.Test;

import java.awt.*;
import java.awt.image.BufferedImage;

import static org.junit.Assert.*;

public class TuiterLiteTest {

  private TuiterLite<Image> tuiterLite;
  private Usuario usuario;

  @Before
  public void setUp() throws UsuarioJaExisteException {
    tuiterLite = new TuiterLite<>();

    usuario = tuiterLite.cadastrarUsuario("Fulano", "fulano@teste.com");

    Image foto = new BufferedImage(100, 100, BufferedImage.TYPE_INT_RGB);
    usuario.setFoto(foto);
  }

  @Test
  public void testeUsuariosReconhecidosCorretamente() {
    assertEquals("Duas instâncias de Usuario devem ser consideradas iguais se possuirem o mesmo email", this.usuario,
        new Usuario("Fulano de Tal", "fulano@teste.com"));
  }

  @Test
  public void testeAutorDoTuite()
      throws TamanhoMaximoExcedidoException, UsuarioDesconhecidoException, TextoVazioException {
    Tuite<Image> tuite = tuiterLite.tuitarAlgo(usuario, "Testando");
    assertEquals("O tuíte deve retornar corretamente seu autor", usuario, tuite.getAutor());
  }

  @Test
  public void testeTamanhoTuite()
      throws UsuarioDesconhecidoException, TamanhoMaximoExcedidoException, TextoVazioException {
    final int tamanho = TuiterLite.TAMANHO_MAXIMO_TUITES + 1;

    StringBuilder sb = new StringBuilder();
    for (int i = 1; i <= tamanho; i++) {
      sb.append("x");
    }
    String texto = sb.toString();

    try {
      tuiterLite.tuitarAlgo(usuario, texto);
      fail("Um tuite maior do que o tamanho máximo deve lançar uma TamanhoMaximoExcedidoException");
    } catch (TamanhoMaximoExcedidoException e) {
      assertEquals("A exceção deve comunicar corretamente o tamanho do texto que se tentou tuitar", tamanho, e.getTamanhoExcedido());
    }
  }

  @Test
  public void testeAnexo() throws TamanhoMaximoExcedidoException, UsuarioDesconhecidoException, TextoVazioException {
    Tuite<Image> tuite = tuiterLite.tuitarAlgo(usuario, "Testando");

    // vamos anexar a foto do usuário no tuíte que ele acabou de fazer
    tuite.anexarAlgo(usuario.getFoto());
    assertEquals("O tuíte deve retornar corretamente o objeto que foi anexado a ele", usuario.getFoto(),
        tuite.getAnexo());

    // agora vamos anexar um outro objeto qualquer ao mesmo tuíte
    /*
     * Object objeto = new Object(); tuite.anexarAlgo(objeto);
     * assertEquals("O tuíte deve sobrescrever o anexo anterior (se existir) com o novo anexo"
     * , objeto, tuite.getAnexo());
     */ 
  }

  @Test
  public void testeApenasUmTipoPermitidoComoAnexo() throws TamanhoMaximoExcedidoException, UsuarioDesconhecidoException,
      UsuarioJaExisteException, TextoVazioException {

    TuiterLite<Image> tuiterLiteQueAceitaApenasImagensComoAnexo = new TuiterLite<>();
    tuiterLiteQueAceitaApenasImagensComoAnexo.cadastrarUsuario(usuario.getNome(), usuario.getEmail());
    Tuite<Image> tuite = tuiterLiteQueAceitaApenasImagensComoAnexo.tuitarAlgo(usuario, "Testando");

    // agora vamos anexar
    tuite.anexarAlgo(usuario.getFoto());
    assertNotNull(tuite.getAnexo());
  }

  @Test
  public void testeHashtags() throws TamanhoMaximoExcedidoException, UsuarioDesconhecidoException, TextoVazioException {
    Tuite<Image> tuite = tuiterLite.tuitarAlgo(usuario, "#LAB7 Testando algo com #hashtag ao longo... #teste");

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

  @Test
  public void testarMultiplosSimbolosDeHashtag()
      throws UsuarioDesconhecidoException, TamanhoMaximoExcedidoException, TextoVazioException {
    Tuite<Image> tuite = tuiterLite.tuitarAlgo(usuario, "###LAB7 ######LAB7");
    assertTrue("O número de caracteres # não deve importar", tuite.getHashtags().contains("#LAB7"));
    assertFalse("Para consulta, devemos usar sempre uma única #", tuite.getHashtags().contains("###LAB7"));
  }

  @Test
  public void testePerformanceContabilizacaoDasHashtags()
      throws TamanhoMaximoExcedidoException, UsuarioDesconhecidoException, TextoVazioException {

    for (int i = 1; i <= 200_000; i++) {
      String hashtag = String.format("#%d", i);
      tuiterLite.tuitarAlgo(usuario, hashtag);
    }
    tuiterLite.tuitarAlgo(usuario, "#5");
    assertEquals("#5", tuiterLite.getHashtagMaisComum());
  }

  /////
  ///// ATENÇÃO: Este teste deve rodar rapidamente (poucos segundos)
  /////
  @Test
  public void testePerformanceTuites()
      throws UsuarioJaExisteException, TamanhoMaximoExcedidoException, TextoVazioException {
    for (int i = 1; i <= 300_000; i++) {
      String nome = String.format("Usuário %d", i);
      String email = String.format("usuario%d@email.com", i);
      tuiterLite.cadastrarUsuario(nome, email);
    }

    Usuario usuarioNaoCadastrado = new Usuario("Usuário Desconhedido", "unknown@void.com");
    for (int i = 1; i <= 300_000; i++) {
      try {
        tuiterLite.tuitarAlgo(usuarioNaoCadastrado, "Teste");
      } catch (UsuarioDesconhecidoException e) {
        // ok, essa exceção é esperada
      }
    }
  }

  @Test
  public void testeTuiteComUsuarioNulo() throws UsuarioDesconhecidoException, TamanhoMaximoExcedidoException, TextoVazioException {
    try {
      tuiterLite.tuitarAlgo(null, "texto");
      fail("Não pode haver tuiter com usuário nulo");
    } catch (Exception e) {
      assertEquals(e.getMessage(), "Usuário ou Tuite nulos.");
    }
  }

  @Test
  public void testeTuiteComTextoNulo() throws UsuarioDesconhecidoException, TamanhoMaximoExcedidoException, TextoVazioException {
    try {
      tuiterLite.tuitarAlgo(this.usuario, null);
      fail("Não pode haver tuiter com texto nulo");
    } catch (Exception e) {
      assertEquals(e.getMessage(), "Usuário ou Tuite nulos.");
    }
  }
  
  @Test
  public void testeTuiteComTextoVazio() throws UsuarioDesconhecidoException, TamanhoMaximoExcedidoException, TextoVazioException {
    try {
      tuiterLite.tuitarAlgo(this.usuario, "");
      fail("Não pode haver tuiter com texto vazio");
    } catch (TextoVazioException e) {
      assertEquals(e.getMessage(), "O Tuite não pode ser vazio.");
    }
  }

  @Test
  public void testeTuiteComUsuarioDesconhecido() throws UsuarioDesconhecidoException, TamanhoMaximoExcedidoException, TextoVazioException {
    try {
      Usuario novoUsuario = new Usuario("Diego", "email@example.com");
      tuiterLite.tuitarAlgo(novoUsuario, "Olá Mundo !");
      fail("Não pode haver tuiter com usuário desconhecido.");
    } catch (UsuarioDesconhecidoException e) {
      assertEquals(e.getMessage(), "Usuário do Tuite não foi encontrado no nosso Banco de Dados.");
    }
  }
}