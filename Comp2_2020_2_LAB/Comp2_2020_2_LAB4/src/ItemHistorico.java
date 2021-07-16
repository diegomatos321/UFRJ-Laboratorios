public class ItemHistorico {
  private Disciplina disciplinaCursada;
  private float mediaFinal;
  private Periodo periodo;

  ItemHistorico(Disciplina disciplinaCursada, float mediaFinal, Periodo periodo) {
    this.disciplinaCursada = disciplinaCursada;
    this.mediaFinal = mediaFinal;
    this.periodo = periodo;
  }

  public Disciplina getDisciplinaCursada() {
    return disciplinaCursada;
  }

  public float getMediaFinal() {
    return mediaFinal;
  }

  public void setMediaFinal(float mediaFinal) {
    this.mediaFinal = mediaFinal;
  }

  public Periodo getPeriodo() {
    return periodo;
  }
}
