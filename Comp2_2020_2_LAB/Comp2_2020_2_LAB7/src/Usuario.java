import java.awt.*;

public class Usuario {

  private final String email;
  private String nome;
  private Image foto;

  public Usuario(String nome, String email) {
    this.nome = nome;
    this.email = email;
  }

  public void setFoto(Image foto) {
    this.foto = foto;
  }

  public Image getFoto() {
    return this.foto;
  }

  public String getEmail() {
    return this.email;
  }

  public String getNome() {
    return this.nome;
  }

  @Override
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    result = prime * result + ((email == null) ? 0 : email.hashCode());
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
    Usuario other = (Usuario) obj;
    if (email == null) {
      if (other.email != null)
        return false;
    } else if (!email.equals(other.email))
      return false;
    return true;
  }
}
