

/*
  >>>>  OpenBCI Helicopter Throttle Control <<<<<
  
  DS1803 DigiPot from Maxim. This test uses a 50K dual version
  http://web.ece.ucdavis.edu/~mcsg/sustainableENG6/Photos/DS1803.pdf
  Helicopter is a cheapo thing from the amazon
  http://www.amazon.com/Syma-S107-S107G-Helicopter-Gyro/dp/B00F4WMAAW

  I de-soldered the throttle control potentiometer, and wired in some jumpers
  The analog pot from the toy ranges from 0 to 5K
  The digiPot ranges from 0 to 50K, so plan to use only 1/10th of the digiPot wiper range
  

*/



#include <Wire.h>
//  digitPot defines
#define DS_0   0x28  // address for DS1803 is 0101000  pull all address pins down
#define WRITE_P0  0xA9  // 10101001
#define WRITE_P1  0xAA  // 10101010
#define WRITE_BOTH  0xAF  // 10101111 

boolean testingPot = false; // used to test initial pot function
boolean expectingValue = false;

unsigned long throttleTimer;
int throttleDuration = 2000;
byte throttleSetting = 0x00;
byte lastThrottleSetting;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  Serial.println("Copter Control 02");
  throttleSetting = lastThrottleSetting = 0x00;
  setBothWipers(DS_0,throttleSetting);
  Serial.print("trottle: ");Serial.println(throttleSetting);
}

void loop() {
  
  if(millis() - throttleTimer > throttleDuration){ throttleSetting = 0; }
  if(throttleSetting != lastThrottleSetting){
    setWiper0(DS_0,throttleSetting);
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
//      Serial.print("trottle: ");Serial.println(throttleSetting);
      throttleTimer = millis();
      expectingValue = false;
      return;  // get outa here
    }
    
    Serial.print("Received "); Serial.println(inChar);
    switch (inChar) {
     case '$':  // Processing must send the $ to tell Arduino the next value is special
       if(expectingValue){return;}
       expectingValue = true;
       break;
   
       default:
         break;
     }
  }
}
