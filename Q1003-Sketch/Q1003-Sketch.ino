/*
     AUTOR:     BrincandoComIdeias
     APRENDA:   https://cursodearduino.net/
     GIHUB:     https://github.com/canalBrincandoComIdeias
     DATA:      28/11/2022
*/
// INCLUSÃO DE BIBLIOTECAS
#include <VarSpeedServo.h>  // https://github.com/netlabtoolkit/VarSpeedServo
#include <neotimer.h>       // Jose Rullan v1.16

// DEFINIÇÕES
#define volumeMaximo 400
#define volumeMedio 300
#define volumeMinimo 120

#define velocidadeMaxima 90
#define velocidadeMedia 60
#define velocidadeMinima 40

#define INTERVALO 30000

// INSTANCIANDO OBJETOS
VarSpeedServo base;
VarSpeedServo bandeira;

// DECLARAÇÃO DE VARIÁVEIS
int maxVol = 0;
byte velocidade = 0;

// 45 POSIÇÕES DO SERVO DA BASE
byte posX[45] = { 90,
                  97, 104, 111, 119, 126, 133, 140, 147, 154, 165,
                  165,
                  165, 154, 147, 140, 133, 126, 119, 111, 104, 97,
                  90,
                  79, 72, 65, 58, 51, 44, 36, 29, 22, 15,
                  15,
                  15, 22, 29, 36, 44, 51, 58, 65, 72, 79,
                  90
                };
// 45 POSIÇÕES DO SERVO DA BANDEIRA
byte posY[45] = { 83,
                  89, 96, 103, 110, 120, 120, 110, 103, 96, 89,
                  83,
                  72, 65, 59, 52, 45, 45, 52, 59, 65, 72,
                  83,
                  89, 96, 103, 110, 120, 120, 110, 103, 96, 89,
                  83,
                  72, 65, 59, 52, 45, 45, 52, 59, 65, 72,
                  83
                };

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);

  base.attach(8);
  bandeira.attach(9);

  randomSeed(analogRead(A3));
}

void loop() {
  static int i = 0;
  static unsigned long delayVol;
  static int maxVolAnt;

  int vol = analogRead(A0);

  if (vol > maxVol) {
    maxVol = vol;
    delayVol = millis();
  }

  if ((millis() - delayVol) > INTERVALO) {
    maxVol = vol;
  }

  if (maxVol != maxVolAnt) {  // DEU O INTERVALO DE ATUALIZAÇÃO
    // COMPARA A MAIOR LEITURA COM OS NÍVEIS DE VOLUME
    if (maxVol > volumeMaximo) {
      Serial.println("MAXIMO");
      velocidade = velocidadeMaxima;
    } else if (maxVol > volumeMedio) {
      Serial.println("MEDIO");
      velocidade = velocidadeMedia;
    } else if (maxVol > volumeMinimo) {
      Serial.println("MINIMO");
      velocidade = velocidadeMinima;
    } else {
      Serial.println("PARADO");
      velocidade = 0;
    }
  }

  if (velocidade > 0) {
    base.write(posX[i], velocidade);     // BACKGROUND
    base.wait();
    bandeira.write(posY[i], velocidade);  // ESPERA TERMINAR O MOVIMENTO (EFEITO DE DELAY)

    i++;
    if (i >= 45) { // NÃO DEIXA "i" PASSAR DO TAMANHO DO ARRAY
      i = 0;
    }
  }

  maxVolAnt = maxVol;
}
