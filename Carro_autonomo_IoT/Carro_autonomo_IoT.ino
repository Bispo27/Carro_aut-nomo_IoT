#include <SPI.h>
#include <Wire.h>

#define MPU_addr 0x68
#define G 9.80665

float VEL;


float time = 10;

float AccX[10]; //array for the current acceleration after sampling
float AccY[10];
float AccZ[10];


float vXn[10]; //array for the current velocity after integration
float vYn[10];
float vZn[10];

float AccXn; //float for the current acceleration
float AccYn;
float AccZn;

float v2XR; //float for the resulting velocity
float v2YR;
float v2ZR;

float v2XP; //float for the previous velocity
float v2YP;
float v2ZP;





void setup() {
  MPU_init();
  Serial.begin(9600);
}
int dif = 0;
void loop() {
   delay(1);

    UpdateVeloc();
    Serial.print("Vel: "); Serial.println(VEL, 5);
 

}
