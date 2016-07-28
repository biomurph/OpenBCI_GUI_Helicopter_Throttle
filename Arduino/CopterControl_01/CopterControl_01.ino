

/*
  >>>>  OpenBCI Helicopter Throttle Control <<<<<
  
  MCP4351502E/ST (quad 5K) DigiPot from Microchip. 
  http://ww1.microchip.com/downloads/en/DeviceDoc/22242A.pdf
  Helicopter is a cheapo thing from the amazon
  http://www.amazon.com/Syma-S107-S107G-Helicopter-Gyro/dp/B00F4WMAAW

  I de-soldered the throttle control potentiometer, and wired in some jumpers
  The analog pot from the toy ranges from 0 to 5K
  The digiPot ranges from 0 to 5K, so plan to use only 100% of the digiPot wiper range
  

*/



#include <SPI.h>
//  digitPot defines
#define CS  10
#define RST 9

#define READ_REG  0x0C
#define WRITE_REG 0x00
#define INCR  0x04
#define DECR  0x08
#define TCON0 0x40
#define TCON1 0xA0

boolean testingPot = false; // used to test initial pot function
boolean expectingValue = false;
boolean throttling = false;

unsigned long throttleTimer;
int throttleDuration = 2000;
byte throttleSetting = 0x00;
byte lastThrottleSetting;

byte wiper[4] = {0x00, 0x10, 0x60, 0x70}; // address of each wiper register
byte wiperPos[4] = {0x01, 0x02, 0x03, 0x04};
int resistance;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  Serial.println("OpenBCI Alpha Wave Helicopter Control");
  
  pinMode(CS,OUTPUT); digitalWrite(CS,HIGH);
  pinMode(RST,OUTPUT); digitalWrite(RST,LOW); // digipot reset pin active low
  delay(100); digitalWrite(RST,HIGH);

  throttleDown();
  throttleSetting = lastThrottleSetting = 0x00;
  Serial.print("trottle: ");Serial.println(throttleSetting);
}

void loop() {
  
  if((millis() - throttleTimer > throttleDuration) && throttling){
    throttleSetting = 0; 
    throttleDown();
    throttling = false;
    }
  if(throttleSetting != lastThrottleSetting){
    setResistance(throttleSetting);
    Serial.print("trottle: ");Serial.println(throttleSetting,DEC);
    lastThrottleSetting = throttleSetting;
  }
    
  
  eventSerial();
}




void eventSerial(){

    while (Serial.available()) {
    char inChar = (char)Serial.read();
//    Serial.print("Received "); Serial.println(inChar);
    if(expectingValue){
      throttleSetting = byte(inChar - 'A'); // variable is ascii encoded 0=A, 1=B, etc
      throttleSetting = map(throttleSetting, 0,26,0,255);
//      Serial.print("trottle: ");Serial.println(throttleSetting);
      throttleTimer = millis();
      throttling = true;
      expectingValue = false;
      return;  // get outa here
    }
    
    Serial.print("Received "); Serial.println(inChar);
    switch (inChar) {
     case '$':  // Processing must send the $ to tell Arduino the next value is special
       if(expectingValue){return;}
       throttleUp();
       expectingValue = true;
       break;
   
       default:
         break;
     }
  }
}
