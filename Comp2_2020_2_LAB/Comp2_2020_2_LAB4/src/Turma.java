import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

public class Turma {
  private Disciplina disciplinaDaTurma;
  private Periodo periodoDaTurma;
  private Professor professorResponsavel;
  private MonitorDeDisciplina monitorDaDisciplina;
  private Map<Long, Aluno> alunosInscritos = new HashMap<Long, Aluno>();
  private Siguinha SIGA;

  public Turma(Disciplina disciplinaDaTurma, Periodo periodoDaTurma, Professor professorResponsavel, Siguinha SIGA) {
    this.disciplinaDaTurma = disciplinaDaTurma;
    this.periodoDaTurma = periodoDaTurma;
    this.professorResponsavel = professorResponsavel;
    this.SIGA = SIGA;
  }

  public Disciplina getDisciplinaDaTurma() {
    return this.disciplinaDaTurma;
  }

  public void setDisciplinaDaTurma(Disciplina disciplinaDaTurma) {
    this.disciplinaDaTurma = disciplinaDaTurma;
  }

  public Periodo getPeriodoDaTurma() {
    return this.periodoDaTurma;
  }

  public void setPeriodoDaTurma(Periodo periodoDaTurma) {
    this.periodoDaTurma = periodoDaTurma;
  }

  public Professor getProfessorResponsavel() {
    return this.professorResponsavel;
  }

  public void setProfessorResponsavel(Professor professorResponsavel) {
    this.professorResponsavel = professorResponsavel;
  }

  public MonitorDeDisciplina getMonitorDaDisciplina() {
    return monitorDaDisciplina;
  }

  public void setMonitorDaDisciplina(MonitorDeDisciplina monitorDaDisciplina) {
    this.monitorDaDisciplina = monitorDaDisciplina;
  }

  public void inscreverAluno(Aluno aluno) {
    Aluno alunoCadastradoNoSIGA = this.SIGA.obterAluno(aluno.getDre());

    if (alunoCadastradoNoSIGA != null) {
      this.alunosInscritos.putIfAbsent(alunoCadastradoNoSIGA.getDre(), alunoCadastradoNoSIGA);
    }
  }

  public void atribuirMediaFinal(Long DRE, float Nota) {
    Aluno alunoCadastradoNoSIGA = this.SIGA.obterAluno(DRE);

    if (alunoCadastradoNoSIGA != null) {
      alunoCadastradoNoSIGA.inserirItemHistorico(this.disciplinaDaTurma, Nota, this.periodoDaTurma);
    }
  }

  public float obterMediaFinal(long DRE) {
    Aluno alunoCadastradoNoSIGA = this.SIGA.obterAluno(DRE);
    float mediaFinal = 0;

    if (alunoCadastradoNoSIGA != null) {
      ItemHistorico itemDoHistoricoDoAluno = alunoCadastradoNoSIGA.getHistoricoDaDisciplina(this.disciplinaDaTurma);

      if (itemDoHistoricoDoAluno != null) {
        mediaFinal = itemDoHistoricoDoAluno.getMediaFinal();
      }
    }
    return mediaFinal;
  }

  public Collection<Aluno> listarAlunos() {
    return this.alunosInscritos.values();
  }
}
