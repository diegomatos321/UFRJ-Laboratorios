public class Pessoa {
  protected String nome;
  protected int anoNascimento;
  public final static int TAMANHO_MAXIMO_DO_NOME = 30;

  public Pessoa(String nome) {
    this.setNome(nome);
  }

  public void setNome(String nome) {
    if (this.validarNome(nome)) {
      this.nome = nome;
    }
  }

  private boolean validarNome(String nome) {
    return nome.length() < TAMANHO_MAXIMO_DO_NOME;
  }

  public String getNome() {
    return this.nome;
  }

  public int getAnoNascimento() {
    return this.anoNascimento;
  }

  public void setAnoNascimento(int anoNascimento) {
    this.anoNascimento = anoNascimento;
  }
}
