float UpdateVeloc(unsigned long tempo) {

  int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

  Wire.beginTransmission(0x68);
  Wire.write(0x3B);  //Primeiro endereco de dados do sensor
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(0x68, 14, true);
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)


  AccXY = sqrt(AcX*AcX+AcY*AcY)*9.81/32767;
  //Serial.print("AccXY"); Serial.println(AccXY, 20);
  // Converte o valor medido
  aceleracoesX[contagem] = (((float)AcX - (-32768)) * (2 - (-2)) / (32768 - (-32768)) + (-2)) * 9.81;
  aceleracoesY[contagem] = (((float)AcY - (-32768)) * (2 - (-2)) / (32768 - (-32768)) + (-2)) * 9.81;

  // Calcula as velocidades pela regra do trapézio
  for (int i = 1; i < 10; i++) {
    velocidadesX[i] =  (aceleracoesX[i - 1] + aceleracoesX[i]) * tempo / 2000000;
    velocidadesX[i] += velocidadesX[i - 1];
    velocidadesY[i] =  (aceleracoesY[i - 1] + aceleracoesY[i]) * tempo / 2000000;
    velocidadesY[i] += velocidadesY[i - 1];
    //Serial.print(velocidadesX[i]);
  }
  if (contagem == 9) {
    contagem = 0;
  } else {
    contagem++;
  }


  //Armazena a ultima velocidade para ser a primeira de todas da próxima medição
  VEL = sqrt(velocidadesX[10] * velocidadesX[10] + velocidadesY[10] * velocidadesY[10]);



}

void UpdateCurrent() {
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
}

void SandData() {
  Serial.print("Corrente Bateria: "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Tensao Bateria: "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Potencia comsumida: "); Serial.print(power_mW); Serial.println("mW");
  Serial.print("Velocidade: "); Serial.print(VEL / 3.6);Serial.println(" Km/h");
  Serial.print("Aceleracao: "); Serial.print(AccXY, 5); Serial.println(" m/s²");
  Serial.println();
}

void GetVelocity() {

}
void NEXTSTATE(STATECAR state) {
  switch (state) {
    case 0:
      {
        Serial.println(pos);
        //        Front(50);
        break;
      }
    case 1:
      {
        Serial.println(pos);
        Left(50);
        break;
      }
    case 2:
      {
        Serial.println(pos);
        Right(50);
        break;
      }
    case 3:
      {
        Serial.println(pos);
        Off();
        break;
      }
  }
}

void Front(int velL, int velR) {
  analogWrite(pinRIGHT, velR / 2);
  analogWrite(pinLEFT, velL / 2);

}

void Right(float vel) {
  digitalWrite(pinRIGHT, LOW);
  digitalWrite(pinLEFT, HIGH);

}
void Left(float vel) {
  digitalWrite(pinRIGHT, HIGH);
  digitalWrite(pinLEFT, LOW);

}

void Off() {
  digitalWrite(pinRIGHT, LOW);
  digitalWrite(pinLEFT, LOW);
}
void UpdadeServo() {
  long microsec;
  servo.write(30);
  delay(100);
  microsec = ultrasonic.timing();
  distCMRight = ultrasonic.convert(microsec, Ultrasonic::CM);
  if (distCMRight > 100) distCMRight = 100;
  delay(100);

  servo.write(105);
  delay(100);
  microsec = ultrasonic.timing();
  distCMCentral = ultrasonic.convert(microsec, Ultrasonic::CM);
  if (distCMCentral > 100) distCMCentral = 100;
  delay(100);

  servo.write(180);
  delay(100);
  microsec = ultrasonic.timing();
  distCMLeft = ultrasonic.convert(microsec, Ultrasonic::CM);
  if (distCMLeft > 100) distCMLeft = 100;
  delay(100);
}
void UpdateFuzzy() {
  int input = (int)distCMCentral * 80 / 100;
  fuzzy->setInput(1, input);
  // Running the Fuzzification
  fuzzy->fuzzify();
  // Running the Defuzzification
  float outputCentral = fuzzy->defuzzify(1);

  input = (int)distCMLeft * 80 / 100;
  fuzzy->setInput(1, input);
  // Running the Fuzzification
  fuzzy->fuzzify();
  // Running the Defuzzification
  float outputLeft = fuzzy->defuzzify(1);

  input = (int)distCMRight * 80 / 100;
  fuzzy->setInput(1, input);
  // Running the Fuzzification
  fuzzy->fuzzify();
  // Running the Defuzzification
  float outputRight = fuzzy->defuzzify(1);
  Front(outputRight * 200 / 50 + 50, outputLeft * 200 / 50 + 50);
  Serial.print("outputRight: ");Serial.print(outputRight * 200 / 50 + 50);
  Serial.print("outputLeft: ");Serial.print(outputLeft * 200 / 50 + 50);
}
