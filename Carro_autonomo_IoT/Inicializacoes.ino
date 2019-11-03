void MPU_init(){
  /*Configurando o modo de operação do sensor*/
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  /*Configurando o fundo de escala do acelerometro */
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);
  Wire.write(0x00);
 /*Configura o fundo de escala do giroscopio*/
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  
}
