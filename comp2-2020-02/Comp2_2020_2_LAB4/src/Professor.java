public class Professor extends Pessoa{
  private int anoContratacao;

  public Professor(String nome, int anoContratacao) {
    super(nome);
    
    this.anoContratacao = anoContratacao;
  }

  public int getAnoContratacao() {
    return this.anoContratacao;
  }

  public void setAnoContratacao(int anoContratacao) {
    this.anoContratacao = anoContratacao;
  }
}
