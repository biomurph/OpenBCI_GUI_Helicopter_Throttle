

/*

  DS1803 DigiPot from Maxim. This test uses a 50K dual version

*/



#include <Wire.h>


#define DS_0   0x28  // address for DS1803 is 0101000  pull all address pins down
#define WRITE_P0  0xA9  // 10101001
#define WRITE_P1  0xAA  // 10101010
#define WRITE_BOTH  0xAF  // 10101111 


boolean testingPot = false;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  Serial.println("DigiPot Test");
  
  setBothWipers(DS_0,0);
}

void loop() {
  
    for(int i=0; i<25; i++){
      eventSerial();
      if(testingPot){
        setBothWipers(DS_0,i);
        readWipers(DS_0);
        delay(500);
      }else{return;}
    }
    for(int i=25; i>0; i--){
      eventSerial();
      if(testingPot){
        setBothWipers(DS_0,i);
        readWipers(DS_0);
        delay(500);
      }else{return;}
    }
    
  eventSerial();
}


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

void eventSerial(){
  if(Serial.available()){
    char token = Serial.read();
    if(token == 'x'){
      testingPot = true;
    }
    if(token == 'p'){
      testingPot = false;
      setWiper0(DS_0,0);
    }
  }
}
