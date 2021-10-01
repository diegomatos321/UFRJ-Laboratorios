import java.util.ArrayList;
import java.util.Objects;

public class Aluno extends Pessoa{
  private final long dre; 

  private float cra;
  private float numeradorCra;
  private float denominadorCra;

  private int creditosAcumulados;
  private ArrayList<ItemHistorico> historico;
  private Periodo periodoIngresso;

  public Aluno() {
    this(0, "Sem Nome"); // chamando a sobrecarga de construtor deste objeto
  }

  public Aluno(long dre, String nome) {
    super(nome);

    this.dre = dre;
    this.nome = nome;

    this.historico = new ArrayList<>(); // com <>, o compilador substitui por <ItemHistorico>

    this.periodoIngresso = Siguinha.obterPeriodoCorrente();

    this.cra = 0; // desnecessário, pois 0 é o valor default de float
    this.numeradorCra = 0;
    this.denominadorCra = 0;

    this.creditosAcumulados = 0; // idem para int
  }

  public float getCra() {
    return cra;
  }

  public int getCreditosAcumulados() {
    return creditosAcumulados;
  }

  public long getDre() {
    return dre;
  }

  public int getIdade() {
    return Siguinha.obterAnoCorrente() - this.anoNascimento;
  }

  public void inserirItemHistorico(Disciplina disciplina, float mediaFinal) {
    Periodo periodoCorrente = Siguinha.obterPeriodoCorrente();
    inserirItemHistorico(disciplina, mediaFinal, periodoCorrente);
  }

  public void inserirItemHistorico(Disciplina disciplina, float mediaFinal, Periodo periodo) {

    boolean disciplinaJaExistenteNoPeriodo = false;

    // verifica se já existe no histórico essa disciplina nesse período
    for (ItemHistorico itemHistorico : this.historico) {

      if (itemHistorico == null) {
        break;
      }

      if (itemHistorico.getDisciplinaCursada() == disciplina && itemHistorico.getPeriodo() == periodo) {

        disciplinaJaExistenteNoPeriodo = true;

        int creditosDaDisciplina = itemHistorico.getDisciplinaCursada().getCreditos();
        this.numeradorCra -= itemHistorico.getMediaFinal() * creditosDaDisciplina;
        if (itemHistorico.getMediaFinal() >= Siguinha.MEDIA_MINIMA_PARA_APROVACAO) {
          this.creditosAcumulados -= creditosDaDisciplina;
        }

        itemHistorico.setMediaFinal(mediaFinal);
      }
    }

    if (!disciplinaJaExistenteNoPeriodo) {
      // inserir item no histórico

      ItemHistorico novoItem = new ItemHistorico(disciplina, mediaFinal, periodo);
      this.historico.add(novoItem);
    }

    // atualizar creditos
    if (mediaFinal >= Siguinha.MEDIA_MINIMA_PARA_APROVACAO) {
      this.creditosAcumulados += disciplina.getCreditos();
    }

    // outro jeito de atualizar o CRA (melhor performance)
    this.numeradorCra += mediaFinal * disciplina.getCreditos();
    this.denominadorCra += disciplina.getCreditos();
    this.cra = this.numeradorCra / this.denominadorCra;
  }

  public String getHistoricoParaImpressao() {
    String resultado = "Aluno(a): " + this.nome + " (DRE: " + this.dre + ")\n";
    for (int i = 0; i < this.historico.size(); i++) {
      ItemHistorico itemHistorico = this.historico.get(i);
      resultado += itemHistorico.getPeriodo().getAno();
      resultado += ".";
      resultado += itemHistorico.getPeriodo().getSemestre();
      resultado += " - ";
      resultado += itemHistorico.getDisciplinaCursada().getNome();
      resultado += " - ";
      resultado += String.format("%.1f", itemHistorico.getMediaFinal());
      if (i != this.historico.size() - 1) { // se não é o último item...
        resultado += "\n";
      }
    }
    return resultado;
  }

  public ItemHistorico getHistoricoDaDisciplina(Disciplina disciplinaDesejada) {
    ItemHistorico historicoDesejado = null;

    for (ItemHistorico itemHistorico : this.historico) {
      if(itemHistorico.getDisciplinaCursada() == disciplinaDesejada) {
        historicoDesejado = itemHistorico;
        break;
      }
    }

    return historicoDesejado;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o)
      return true;
    if (o == null || getClass() != o.getClass())
      return false;
    Aluno aluno = (Aluno) o;
    return dre == aluno.dre && Objects.equals(nome, aluno.getNome());
  }
}