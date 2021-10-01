public class Dimensoes {

  private int comprimentoEmCentimetros;
  private int larguraEmCentimetros;
  private int alturaEmCentimetros;
  private int volumeEmCentimetrosCubicos;
  private int pesoEmGramas;

  public Dimensoes(int comprimentoEmCentimetros, int larguraEmCentimetros, int alturaEmCentimetros,
      int volumeEmCentimetrosCubicos, int pesoEmGramas) {
    this.comprimentoEmCentimetros = comprimentoEmCentimetros;
    this.larguraEmCentimetros = larguraEmCentimetros;
    this.alturaEmCentimetros = alturaEmCentimetros;
    this.volumeEmCentimetrosCubicos = volumeEmCentimetrosCubicos;
    this.pesoEmGramas = pesoEmGramas;
  }

  public int getComprimentoEmCentimetros() {
    return comprimentoEmCentimetros;
  }

  public void setComprimentoEmCentimetros(int comprimentoEmCentimetros) {
    this.comprimentoEmCentimetros = comprimentoEmCentimetros;
  }

  public int getLarguraEmCentimetros() {
    return larguraEmCentimetros;
  }

  public void setLarguraEmCentimetros(int larguraEmCentimetros) {
    this.larguraEmCentimetros = larguraEmCentimetros;
  }

  public int getAlturaEmCentimetros() {
    return alturaEmCentimetros;
  }

  public void setAlturaEmCentimetros(int alturaEmCentimetros) {
    this.alturaEmCentimetros = alturaEmCentimetros;
  }

  public int getVolumeEmCentimetrosCubicos() {
    return volumeEmCentimetrosCubicos;
  }

  public void setVolumeEmCentimetrosCubicos(int volumeEmCentimetrosCubicos) {
    this.volumeEmCentimetrosCubicos = volumeEmCentimetrosCubicos;
  }

  public int getPesoEmGramas() {
    return pesoEmGramas;
  }

  public void setPesoEmGramas(int pesoEmGramas) {
    this.pesoEmGramas = pesoEmGramas;
  }

  
}
