#include <SoftwareSerial.h>
SoftwareSerial soft(2,3); // 2 : RX , 3 : TX

char ch;
  
void setup() {
  Serial.begin(115200);
  soft.begin(115200);
}

void loop() {


  if(Serial.available()){
    ch = Serial.read();
    soft.write(ch);
    //Serial.write(ch);
  }
  if(soft.available()){
    Serial.write(soft.read());
  }
  //delay(1500);
}
