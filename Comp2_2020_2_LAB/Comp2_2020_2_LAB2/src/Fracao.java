/**
 * Nome: Diego Vasconcelos Schardosim de Matos
 * DRE: 120098723
 */

/**
 * Representa uma fração de forma explícita, guardando numerador e denominador
 * inteiros. Frações equivalentes (matematicamente) devem ser consideradas
 * equals().
 */

public class Fracao {

  private int numerador;
  private int denominador;
  private boolean sinal;

  /**
   * Cria uma fração, baseada em seu numerador e denominador. O sinal da fração
   * será inferido a partir do sinal do numerador e do denominador.
   *
   * @param numerador   o numerador
   * @param denominador o denominador
   */
  public Fracao(int numerador, int denominador) {

    if (denominador == 0) {
      throw new ArithmeticException("Denominador não pode ser zero!!");
    }

    this.numerador = Math.abs(numerador);
    this.denominador = Math.abs(denominador);

    if (numerador == 0) {
      this.sinal = true;
    } else if ((numerador < 0 || denominador < 0) && !(numerador < 0 && denominador < 0)) {
      this.sinal = false;
    } else {
      this.sinal = true;
    }
  }

  /**
   * Retorna o sinal da fração.
   *
   * @return true, se for positiva ou nula (zero); false, se for negativa.
   */
  public boolean getSinal() {
    return this.sinal;
  }

  /**
   * Retorna o (valor absoluto do) numerador desta fração, ou seja, sempre
   * não-negativo
   * 
   * @return o numerador
   */
  public int getNumerador() {
    return this.numerador;
  }

  /**
   * Retorna o (valor absoluto do) denominador desta fração, ou seja, sempre
   * positivo
   * 
   * @return o numerador
   */
  public int getDenominador() {
    return this.denominador;
  }

  /**
   * Retorna o valor numérico da fração (com o sinal correto).
   *
   * @return um float, com o valor na melhor precisão possível Ex.: -1/3 vai
   *         retornar -0.33333333
   */
  public float getValorNumerico() {
    float valorNumerico = (float) this.numerador / this.denominador;

    if (!sinal) {
      valorNumerico *= -1;
    }

    return valorNumerico;
  }

  /**
   * Retorna uma fração equivalente à esta fração, e que não pode mais ser
   * simplificada (irredutível).
   *
   * @return um outro objeto Fracao, se esta fração for redutível; esta própria
   *         fração (this), se ela já for irredutível
   */
  public Fracao getFracaoGeratriz() {
    int mdc = AritmeticaUtils.mdc(this.numerador, this.denominador);

    /* Primos entre si */
    if (mdc == 1) {
      return this;
    }

    Fracao fracaoGeratriz = new Fracao(this.numerador / mdc, this.denominador / mdc);

    return fracaoGeratriz; 
  }

  @Override
  public String toString() {
    String stringDaFracao = "";
    String stringDoSinal = "";

    if (this.numerador == 0) {
      stringDaFracao = "0";

      return stringDaFracao;
    }

    if (!sinal) {
      stringDoSinal = "-";
    }

    if (this.denominador == 1) {
      stringDaFracao = stringDoSinal + this.numerador;
    }
    else {
      stringDaFracao = stringDoSinal + this.numerador + "/" + this.denominador;
    }

    return stringDaFracao;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj) return true;
    if (obj == null || getClass() != obj.getClass()) return false;

    Fracao other = (Fracao) obj;

    return this.getValorNumerico() == other.getValorNumerico();
  }
}
