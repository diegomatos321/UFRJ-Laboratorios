/* 
  Repositorio: https://github.com/diegomatos321/Linguagem-C-Pratica
  
  PARTE 01:
  1. Em um programa em C, crie as variáveis hora, minuto e segundo, atribuindo-as
  valores inteiros;

  2. Você quer converter a hora armazenada nas variáveis hora e minuto para segundos
  e descobrir quantos segundos se passaram desde a meia-noite de hoje. Para isso,
  você irá atribuir o resultado a variável tempo_total_segundos e fazer os cálculos
  necessários.

  3. Na sua aplicação, o valor atribuído à variável tempo_total_segundos corresponde ao
  tempo que foi necessário para percorrer uma distância, armazenada na variável
  distancia. Calcule a variável velocidade_media, que será atribuída com o cálculo da
  divisão da distância pelo tempo necessário para percorrê-la.

  4. A velocidade média, armazenada na variável velocidade_media, está em m/s.
  Entretanto, seu chefe irá apresentar esse sistema para um grupo de americanos.
  Faça com que o valor atribuído à variável velocidade_media esteja em milhas por
  hora. DICA: 1 m/s = 2,23694 mph

  PARTE 02:
  5. O volume (v) de uma esfera pode ser calculada através de v = 4/3πr³ , onde r é o raio
  da esfera. Qual o volume de uma esfera cujo raio é igual a 5 ? DICA: pi = 3.14159.

  PARTE 03:
  6. Armazene o valor de uma temperatura em graus celsius numa variável. Converta
  essa temperatura para graus fahrenheit. DICA: F = (9*C)/5 + 32.

  7. E converter a mesma temperatura em graus celsius para Kelvin? Lembrando que K =
  -272,15 oC.

  PARTE 04:
  8. Se eu preciso chegar ao Fundão às 8 horas pegando 2 ônibus, dos quais o primeiro
  percorre 15 km com uma média de 25km/h e o segundo percorre 10km a uma média
  de 30 km/h, que horas eu preciso sair de casa se o tempo máximo total que eu fico
  esperando os ônibus é de 15 minutos?
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/* #include "./utils/handleError.h" */
#include "./utils/pressioneEnterParaContinuar.h"

void resolverPrimeiraTarefa();
struct tm* getTimeNow();
int converterHorasParaSegundos(int horas);
int converterMinutosParaSegundos(int minutos);
double converterVelocidadeParaMilhas(double velocidadeMedia);

void resolverSegundaTarefa();

void resolverTerceiraTarefa();
double converterGrausParaFahrenheit(double graus);
double converterGrausParaKelvin(double tempGraus);

void resolverQuartaTarefa();

const int eACENTUADO = 130, uACENTUADO = 163, iACENTUADO = 161, CEDILHA = 135, aCOMTIL = 198, aCIRCUNFLEXO = 131, aCRASEADO = 133, GRAU = 167, eCIRCUNFLEXO = 136, aACENTUADO = 160, oCIRCUNFLEXO = 147;

int main()
{
  resolverPrimeiraTarefa();
  resolverSegundaTarefa();
  resolverTerceiraTarefa();
  resolverQuartaTarefa();
  return 0;
}

void resolverPrimeiraTarefa()
{
  int horas, minutos, segundos, horasEmSegundos, minutosEmSegundos, tempoTotalSegundos;
  double distancia, velocidadeMedia, velocidadeMediaEmMilhas;
  struct tm *instanteAtual = getTimeNow();

  system("cls");
  printf("=== Primeiro Algoritmo ===\n");

  horas = instanteAtual -> tm_hour;
  minutos = instanteAtual -> tm_min;
  segundos = instanteAtual -> tm_sec;

  horasEmSegundos = converterHorasParaSegundos(horas);
  minutosEmSegundos = converterMinutosParaSegundos(minutos);

  tempoTotalSegundos = horasEmSegundos + minutosEmSegundos + segundos;
  printf("Tempo total em segundos: %i \n", tempoTotalSegundos);

  printf("Digite a dist%cncia percorrida, em metros: \n", aCIRCUNFLEXO);
  scanf("%lf", &distancia);

  velocidadeMedia = distancia / tempoTotalSegundos;

  printf("A velocidade m%cdia: %0.2lf m/s \n", eACENTUADO, velocidadeMedia);

  velocidadeMediaEmMilhas = converterVelocidadeParaMilhas(velocidadeMedia);

  printf("A velocidade m%cdia em milhas por hora: %0.2lf mph \n", eACENTUADO, velocidadeMediaEmMilhas);
  pressioneEnterParaContinuar();
}

struct tm* getTimeNow()
{
  struct tm *localTime;
  time_t now;
  time(&now);
  localTime = localtime(&now);

  return localTime;
}

int converterHorasParaSegundos(int horas)
{
  return 60 * 60 * horas;
}

int converterMinutosParaSegundos(int minutos)
{
  return 60 * minutos;
}

double converterVelocidadeParaMilhas(double velocidadeMedia)
{
  const double MILHA_POR_METRO = 2.23694;

  return velocidadeMedia * MILHA_POR_METRO;
}

void resolverSegundaTarefa()
{
  const double PI = 3.14159;
  double raio, volumeEsfera;

  system("cls");
  printf("=== Segundo Algoritmo ===\n");
  printf("=== Calcular Volume da Esfera ===\n");
  printf("Digite o Raio da Esfera: ");
  scanf("%lf", &raio);

  volumeEsfera = (double)4/3 * PI * pow(raio, 3);

  printf("O volume de uma esfera de raio %.2lf %c %.2lf\n", raio, eACENTUADO, volumeEsfera);
  pressioneEnterParaContinuar();
}

void resolverTerceiraTarefa()
{
  double tempGraus, tempFahrenheit, tempKelvin;

  system("cls");
  printf("=== Terceiro Algoritmo ===\n");
  printf("=== Converter de Graus Celsius para Fahrenheit e Kelvin ===\n");
  printf("Digite a temperatura, em Graus Celsius, a ser convertida: ");
  scanf("%lf", &tempGraus);

  tempFahrenheit = converterGrausParaFahrenheit(tempGraus);
  printf("A temperatura %.2lf%cc em Fahrenheit %c: %.2lfF\n", tempGraus, GRAU, eACENTUADO, tempFahrenheit);

  tempKelvin = converterGrausParaKelvin(tempGraus);
  printf("A temperatura %.2lf%cc em Kelvin %c: %.2lfK\n", tempGraus, GRAU, eACENTUADO, tempKelvin);
  pressioneEnterParaContinuar();
}

double converterGrausParaFahrenheit(double graus)
{
  return (9 * graus) / 5 + 32;
}

double converterGrausParaKelvin(double tempGraus)
{
  return tempGraus + 272.15;
}

void resolverQuartaTarefa()
{
  double horaDeChegada, numeroDeOnibus, tempoDeTransporte = 0, horaDeSaida = 0, tempoDeEspera, minutos;
  int horas;
  unsigned int i;

  system("cls");
  printf("=== Quarto Algoritmo ===\n");
  printf("Vamos descobrir o hor%crio aproximado que voc%c precisa sair de casa para chegar a tempo na UFRJ\n", aACENTUADO, eCIRCUNFLEXO);
  printf("Primeiramente, qual %c o hor%crio da sua primeira aula ? ", eACENTUADO, aACENTUADO);
  scanf("%lf", &horaDeChegada);
  printf("E quantos %cnibus voc%c pega ? ", oCIRCUNFLEXO, eCIRCUNFLEXO);
  scanf("%lf", &numeroDeOnibus);

  for (i = 0; i < numeroDeOnibus; i++)
  {
    double velocidadeMedia, deslocamento, intervaloDeTempo;

    printf("Qual %c a velocidade m%cdia do %i%c %cnibus, em Km/h ? ", eACENTUADO, eACENTUADO, i+1, GRAU,oCIRCUNFLEXO);
    scanf("%lf", &velocidadeMedia);

    printf("Qual %c o deslocamento do %i%c %cnibus em Km ? ", eACENTUADO, i+1, GRAU, oCIRCUNFLEXO);
    scanf("%lf", &deslocamento);

    intervaloDeTempo = deslocamento / velocidadeMedia ;
    tempoDeTransporte += intervaloDeTempo;
  }
  
  printf("Quanto tempo voc%c espera, em minutos, no ponto de onibus ? ", eCIRCUNFLEXO);
  scanf("%lf", &tempoDeEspera);

  tempoDeEspera /= 60;
  tempoDeTransporte += tempoDeEspera;

  horaDeSaida = horaDeChegada - tempoDeTransporte;

  system("cls");

  if (horaDeSaida < 0)
  {
    unsigned int ciclosCompletos = abs(horaDeSaida) / 24.0 + 1.0;

    horaDeSaida += 24 * ciclosCompletos;
  }

  horas = (int)horaDeSaida;
  minutos = (horaDeSaida - horas) * 60;

  printf("Muito Bem ! Voc%c precisa estar no ponto de %cnibus %cs: %i Horas e %.0lf Minutos", eCIRCUNFLEXO, oCIRCUNFLEXO, aCRASEADO, horas, minutos);
}
