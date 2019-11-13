void MPUInit(){
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

void CurrentInit(){
  
}

void FuzzyInit(){
    // Instantiating a FuzzyInput object
  FuzzyInput *distance = new FuzzyInput(1);
  // Instantiating a FuzzySet object
  FuzzySet *small = new FuzzySet(0, 20, 20, 40);
  // Including the FuzzySet into FuzzyInput
  distance->addFuzzySet(small);
  // Instantiating a FuzzySet object
  FuzzySet *safe = new FuzzySet(30, 50, 50, 70);
  // Including the FuzzySet into FuzzyInput
  distance->addFuzzySet(safe);
  // Instantiating a FuzzySet object
  FuzzySet *big = new FuzzySet(60, 80, 80, 80);
  // Including the FuzzySet into FuzzyInput
  distance->addFuzzySet(big);
  // Including the FuzzyInput into Fuzzy
  fuzzy->addFuzzyInput(distance);

  // Instantiating a FuzzyOutput objects
  FuzzyOutput *speed = new FuzzyOutput(1);
  // Instantiating a FuzzySet object
  FuzzySet *slow = new FuzzySet(0, 10, 10, 20);
  // Including the FuzzySet into FuzzyOutput
  speed->addFuzzySet(slow);
  // Instantiating a FuzzySet object
  FuzzySet *average = new FuzzySet(10, 20, 30, 40);
  // Including the FuzzySet into FuzzyOutput
  speed->addFuzzySet(average);
  // Instantiating a FuzzySet object
  FuzzySet *fast = new FuzzySet(30, 40, 40, 50);
  // Including the FuzzySet into FuzzyOutput
  speed->addFuzzySet(fast);
  // Including the FuzzyOutput into Fuzzy
  fuzzy->addFuzzyOutput(speed);

  // Building FuzzyRule "IF distance = small THEN speed = slow"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifDistanceSmall = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifDistanceSmall->joinSingle(small);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenSpeedSlow = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenSpeedSlow->addOutput(slow);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenSpeedSlow);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule01);

  // Building FuzzyRule "IF distance = safe THEN speed = average"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifDistanceSafe = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifDistanceSafe->joinSingle(safe);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenSpeedAverage = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenSpeedAverage->addOutput(average);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifDistanceSafe, thenSpeedAverage);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule02);

  // Building FuzzyRule "IF distance = big THEN speed = high"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifDistanceBig = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifDistanceBig->joinSingle(big);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenSpeedFast = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenSpeedFast->addOutput(fast);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifDistanceBig, thenSpeedFast);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule03);
}


void UltrassonicInit(){
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
}

void pontH(){
  pinMode(pinRIGHT, OUTPUT);
  pinMode(pinLEFT, OUTPUT);
  State = FRONT;
}
