package modelo;

public class Livro {
  private String titulo;
  private String autor;
  private int anoDePublicacao;

  public Livro(String titulo, String autor, int anoDePublicacao) {
    this.titulo = titulo;
    this.autor = autor;
    this.anoDePublicacao = anoDePublicacao;
  }

  public String getTitulo() {
    return titulo;
  }

  public String getAutor() {
    return autor;
  }

  public int getAnoDePublicacao() {
    return anoDePublicacao;
  }

  @Override
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    result = prime * result + anoDePublicacao;
    result = prime * result + ((titulo == null) ? 0 : titulo.hashCode());
    return result;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (obj == null)
      return false;
    if (getClass() != obj.getClass())
      return false;
    Livro other = (Livro) obj;
    if (anoDePublicacao != other.anoDePublicacao)
      return false;
    if (titulo == null) {
      if (other.titulo != null)
        return false;
    } else if (!titulo.equals(other.titulo))
      return false;
    return true;
  }
}
