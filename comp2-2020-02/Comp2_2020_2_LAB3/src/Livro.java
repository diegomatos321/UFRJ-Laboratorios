import java.util.Calendar;
import java.util.Date;

public class Livro extends Produto {

  private String editora;
  private String autor;
  private int numeroDePaginas;
  private Calendar anoDePublicacao;

  public Livro(String nome, String descricao, float preco, Dimensoes dimensoes) {
    super(nome, descricao, preco, dimensoes);
  }

  public Livro(String nome, String descricao, float preco, Dimensoes dimensoes, String editora, Calendar anoDePublicacao) {
    this(nome, descricao, preco, dimensoes);

    this.editora = editora;
    this.anoDePublicacao = anoDePublicacao;
  }

  public String getEditora() {
    return editora;
  }

  public void setEditora(String editora) {
    this.editora = editora;
  }

  public String getAutor() {
    return this.autor;
  }

  public void setAutor(String autor) {
    this.autor = autor;
  }

  public int getNumeroDePaginas() {
    return numeroDePaginas;
  }

  public void setNumeroDePaginas(int numeroDePaginas) {
    this.numeroDePaginas = numeroDePaginas;
  }

  public String getTrechoEmDestaque() {
    return this.descricao;
  }

  public int getAnoDePublicacao() {
    return this.anoDePublicacao.get(Calendar.YEAR);
  }
}
