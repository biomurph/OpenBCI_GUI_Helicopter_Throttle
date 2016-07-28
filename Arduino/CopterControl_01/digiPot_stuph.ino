



void throttleDown(){  // set the digipot wipers to full on for lowest current output
  byte command, error;

  digitalWrite(CS,LOW);   // activate with W & B connected, A disconnected
  error = SPI.transfer(TCON0 | WRITE_REG);
  SPI.transfer(0xBF);               // 1011 1111  // connect A for testing resistance
  checkError(error,TCON0);
  digitalWrite(CS,HIGH);
  delay(1);
  digitalWrite(CS,LOW);
  error = SPI.transfer(TCON1 | WRITE_REG);
  SPI.transfer(0xBB);               // 1011 1011
  digitalWrite(CS,HIGH);
  checkError(error,TCON1);

  for(int i=0; i<4; i++){
    digitalWrite(CS,LOW);
    error = SPI.transfer(wiper[i] | WRITE_REG);
    SPI.transfer(0x00);             // connect W to B only see W resistance
    digitalWrite(CS,HIGH);
    checkError(error,wiper[i]);
  }

  Serial.println("throttled down");

}

void throttleUp(){
  byte error;

  digitalWrite(CS,LOW);   // activate with only Pot 0 engaged [lower right]
  error = SPI.transfer(TCON0 | WRITE_REG);
  SPI.transfer(0x8F);               // 1000 1111  // connect A for testing resistance
  checkError(error,TCON0);
  digitalWrite(CS,HIGH);
  delay(10);
  digitalWrite(CS,LOW);
  error = SPI.transfer(TCON1 | WRITE_REG);
  SPI.transfer(0x88);               // 1000 1000
  digitalWrite(CS,HIGH);
  checkError(error,TCON1);
}

void setResistance(byte r){
  byte error;

  digitalWrite(CS,LOW);   // activate with W & B connected, A disconnected
  error = SPI.transfer(wiper[0] | WRITE_REG);
  SPI.transfer(r);           
  digitalWrite(CS,HIGH);    
  checkError(error,wiper[0]);
}

void readWipers(){
  byte error;

  for(int i=0; i<4; i++){
    digitalWrite(CS,LOW);
    error = SPI.transfer(wiper[i] | READ_REG);
    wiperPos[i] = SPI.transfer(0x00); // read wiper values
    digitalWrite(CS,HIGH);
    checkError(error,wiper[i]);
  }
}


void checkError(byte e, byte r){
  if(e != 0xFF){
      Serial.print("\terror: on register "); Serial.println(r,HEX);
    }
}
