
void UpdateVeloc() {
  float AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
  for (int n = 1; n < time; n++) //filling the arrays
  {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  //Primeiro endereco de dados do sensor
    Wire.endTransmission(false);
    //Solicita os dados do sensor
    Wire.requestFrom(MPU_addr, 14, true);
    //Armazena o valor dos sensores nas variaveis correspondentes

    //filling an array with current values of acceleration after sampling
    AccX[n] = (Wire.read() << 8 | Wire.read()) / (2*G); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AccY[n] = (Wire.read() << 8 | Wire.read()) / (2*G); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AccZ[n] = (Wire.read() << 8 | Wire.read()) / (2*G); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    AccXn = AccX[n]; //saving the current vaue of the acceleration array as float for the integration
    AccYn = AccY[n];
    AccZn = AccZ[n];
 
    vXn[n] = vXn[n - 1] + (AccX[n]) * 0.001; //integration
    v2XR = (vXn[n]); //saving the current resultant velocity as a float
    v2XP = vXn[n - 1]; //saving the previous velocity as a float

    vYn[n] = vYn[n - 1] + (AccY[n]) * 0.001;
    v2YR = (vYn[n]);
    v2YP = vYn[n - 1];
  
    vZn[n] = vZn[n - 1] + (AccZ[n]) * 0.001;
    v2ZR = (vZn[n]);
    v2ZP = vZn[n - 1];

    VEL = sqrt(v2XR * v2XR +  v2YR * v2YR);
  }
}
