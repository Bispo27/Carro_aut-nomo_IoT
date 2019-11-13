#include <SPI.h>
#include <Wire.h>
#include <Ultrasonic.h>
#include <Adafruit_INA219.h>
#include <Servo.h>
#include <TimerOne.h>
#include <Fuzzy.h>

#define MPU_addr 0x68
#define G 9.80665
#define TRIGGER_PIN 10 // OUTPUT
#define ECHO_PIN 11 // INPUT

#define VEL_MAX 75
#define pinRIGHT 5
#define pinLEFT 6

#define INITIAL 0
#define LIMIT 180

unsigned long tempo;
// Vetor para guardar os valores de aceleração
float aceleracoesX[10];
float aceleracoesY[10];
// Vetor para guardar os valores de velocidade
float velocidadesX[10];
float velocidadesY[10];
float AccXY, VelXY;
float posicao;
// Variavel para armazenar quantas amostras ja foram pegas


Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Fuzzy *fuzzyCentral = new Fuzzy();
Fuzzy *fuzzyLeft = new Fuzzy();
Fuzzy *fuzzyRight = new Fuzzy();
Fuzzy *fuzzy = new Fuzzy();

Adafruit_INA219 ina219;
Servo servo;

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;

float distCMCentral, distCMRight, distCMLeft;

float VEL;
typedef enum {
  FRONT = 0,
  LEFT = 1,
  RIGHT = 2,
  STOP = 3
} STATECAR;
STATECAR State = STOP;

int contagem = 0;

static float angle = INITIAL;
int pos = 0;
void setup() {
  MPUInit();
  pontH();
  UltrassonicInit();
  servo.attach(3);
  ina219.begin();
  FuzzyInit();
  Serial.begin(9600);
  Serial.println("Vai entrar na rotina");
}
void loop() {
  Serial.println("Entrou na Rotina");
  Serial.println("Entrou");
  for (;;) {
    tempo = micros();
    UpdadeServo();
    UpdateFuzzy();
    UpdateCurrent();
    UpdateVeloc(tempo);
    SandData();
  }


}
