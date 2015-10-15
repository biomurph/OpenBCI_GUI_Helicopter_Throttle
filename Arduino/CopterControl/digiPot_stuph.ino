




void setWiper0(byte address, byte val){
  Wire.beginTransmission(address);  // start transmission to slave 0x
  Wire.write(WRITE_P0);      // sends instruction byte
  Wire.write(val);             // sends potentiometer value byte
  Wire.endTransmission();      // stop transmitting
}

void readWipers(byte address){
//  address ++;
  Wire.requestFrom(address,2);    // 

  while (Wire.available())   // slave may send less than requested
  {
    byte x = Wire.read(); // receive a byte as character
    Serial.print(x,DEC);         // print the character
    Serial.print("  ");
  }
  Serial.println();
}

void setWiper1(byte address, byte val){
  Wire.beginTransmission(address);  // start transmission to slave 0x
  Wire.write(WRITE_P1);      // sends instruction byte
  Wire.write(val);             // sends potentiometer value byte
  Wire.endTransmission();      // stop transmitting
}

void setBothWipers(byte address, byte val){
  Wire.beginTransmission(address);  // start transmission to slave 0x
  Wire.write(WRITE_BOTH);      // sends instruction byte
  Wire.write(val);             // sends potentiometer value byte
  Wire.endTransmission();      // stop transmitting
}


void digiPotTest(){
  for(int i=0; i<25; i++){  // scroll up
      eventSerial();
      if(testingPot){
        setBothWipers(DS_0,i);
        readWipers(DS_0);
        delay(500);
      }else{return;}
    }
    for(int i=25; i>0; i--){  // scroll down
      eventSerial();
      if(testingPot){
        setBothWipers(DS_0,i);
        readWipers(DS_0);
        delay(500);
      }else{return;}
    }
}
