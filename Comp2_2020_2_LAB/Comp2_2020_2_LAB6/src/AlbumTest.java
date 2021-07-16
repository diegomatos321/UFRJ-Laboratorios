import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class AlbumTest {
  private Album<Figurinha> albumFigurinhas;
  private Repositorio<Figurinha> repositorioFigurinhas;

  private Album<Selo> albumSelos;
  private Repositorio<Selo> repositorioSelos;

  private static final int TAMANHO_DO_REPOSITORIO = 200;
  private static final int ITENS_POR_PACOTE = 3;

  @Before // roda antes de cada teste
  public void setUp() {
    this.repositorioFigurinhas = new Repositorio<Figurinha>("album_copa2014", TAMANHO_DO_REPOSITORIO);
    for (Integer i = 1; i <= TAMANHO_DO_REPOSITORIO; i++) {
      this.repositorioFigurinhas.addToRepositorio(new Figurinha(i, "figurinha_" + i));
    }
    this.albumFigurinhas = new Album<Figurinha>(repositorioFigurinhas, ITENS_POR_PACOTE);

    this.repositorioSelos = new Repositorio<Selo>("selos_paises2020", TAMANHO_DO_REPOSITORIO);
    for (Integer i = 1; i <= TAMANHO_DO_REPOSITORIO; i++) {
      this.repositorioSelos.addToRepositorio(new Selo(i, "selo_" + i));
    }
    this.albumSelos = new Album<Selo>(this.repositorioSelos, ITENS_POR_PACOTE);
  }

  private void popularAlbum(int[] posicoesDesejadas) {
    Pacotinho<Figurinha> pacote = new Pacotinho<>(this.repositorioFigurinhas, posicoesDesejadas);
    this.albumFigurinhas.receberNovoPacotinho(pacote);

    Pacotinho<Selo> pacoteDeSelos = new Pacotinho<>(this.repositorioSelos, posicoesDesejadas);
    this.albumSelos.receberNovoPacotinho(pacoteDeSelos);
  }

  @Test
  public void testarPossuiFigurinhaParaFigurinhasExistentes() {
    popularAlbum(new int[] { 1, 2, 3 });

    for (int i = 1; i <= 3; i++) {
      assertTrue("Figurinhas já inseridas devem ser encontradas", this.albumFigurinhas.possuiItemColado(i));
    }
  }

  @Test
  public void testarPossuiFigurinhaParaFigurinhasAusentes() {
    popularAlbum(new int[] { 1, 2, 3 });

    assertFalse("Não devemos encontrar no álbum figurinhas nunca inseridas", this.albumFigurinhas.possuiItemColado(4));
    assertFalse("Não devemos encontrar figurinhas de posições não-positivas",
        this.albumFigurinhas.possuiItemColado(-390));
    assertFalse("Não devemos encontrar figurinhas maiores do que o tamanho",
        this.albumFigurinhas.possuiItemColado(TAMANHO_DO_REPOSITORIO + 1));
  }

  @Test
  public void testarPossuiRepetidaParaFigurinhaRepetida() {
    popularAlbum(new int[] { 1, 2, 3 });
    assertFalse(this.albumFigurinhas.possuiItemRepetido(2)); // sanity check

    popularAlbum(new int[] { 2, 8, 9 });
    assertTrue(this.albumFigurinhas.possuiItemRepetido(2));
  }

  @Test
  public void testarGetTamanhoAlbum() {
    assertEquals(TAMANHO_DO_REPOSITORIO, this.albumFigurinhas.getTamanho());
  }

  @Test
  public void testarGetContFigurinhas() {
    popularAlbum(new int[] { 1, 2, 3 });
    assertEquals(3, this.albumFigurinhas.getQuantItensColados());

    popularAlbum(new int[] { 1, 2, 3 });
    assertEquals(3, this.albumFigurinhas.getQuantItensColados());
  }

  @Test
  public void testarGetQuantasFaltam() {
    popularAlbum(new int[] { 1, 2, 3 });
    assertEquals(TAMANHO_DO_REPOSITORIO - 3, this.albumFigurinhas.getQuantItensFaltantes());
  }

  @Test
  public void testarAutoCompletar() {
    albumFigurinhas.autoCompletar();
    assertEquals("Não deve ser possível auto-completar um álbum que esteja vazio", TAMANHO_DO_REPOSITORIO,
        albumFigurinhas.getQuantItensFaltantes());

    // agora vamos adicionar pacotinhos aleatórios até o álbum ficar quase cheio

    int minimoFigurinhasColadasParaAutoCompletar = (int) (TAMANHO_DO_REPOSITORIO * Album.PERCENTUAL_MINIMO_PARA_AUTO_COMPLETAR
        / 100f);

    while (albumFigurinhas.getQuantItensColados() < minimoFigurinhasColadasParaAutoCompletar) {
      Pacotinho<Figurinha> novoPacotinho = new Pacotinho<>(this.repositorioFigurinhas, ITENS_POR_PACOTE); // aleatório
      albumFigurinhas.receberNovoPacotinho(novoPacotinho);
    }

    // sanity check
    assertTrue(albumFigurinhas.getQuantItensFaltantes() > 0);

    albumFigurinhas.autoCompletar();

    assertEquals(
        "O álbum deve estar completo após uma chamada válida ao auto-completar "
            + "(isto é, após o percentual mínimo de figurinhas já ter sido obtido)",
        0, albumFigurinhas.getQuantItensFaltantes()); // álbum completo!
  }

  @Test
  public void testarGetItemColado() {
    popularAlbum(new int[] { 1, 2, 3 });
    Figurinha figurinha = albumFigurinhas.getItemColado(2);

    assertNotNull(figurinha);

    assertEquals(2, figurinha.getPosicao());

    assertNull(albumFigurinhas.getItemColado(4));
  }

  @Test
  public void testarFigurinhasESelos(){
    popularAlbum(new int[] { 1, 2, 3 });

    for (int i = 1; i <= 3; i++) {
      assertTrue("Figurinhas já inseridas devem ser encontradas", this.albumFigurinhas.possuiItemColado(i));
    }

    for (int i = 1; i <= 3; i++) {
      assertTrue("Figurinhas já inseridas devem ser encontradas", this.albumSelos.possuiItemColado(i));
    }
  }

  @Test
  public void testarRejeicaoPacotinhosDeTamanhoErrado() {
    popularAlbum(new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8 });

    assertEquals("Pacotes de tamanho distinto do informado na construção " + "do álbum devem ser rejeitados", 0,
        albumFigurinhas.getQuantItensColados());
  }

}