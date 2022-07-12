#include <SoftwareSerial.h>
SoftwareSerial esp32(2,3); // 2 : RX , 3 : TX

char ch;
  
void setup() {
  Serial.begin(9600);
  esp32.begin(9600);
}

void loop() {
if(Serial.available()){
    esp32.write(Serial.read());
  }
  if(esp32.available()){
    Serial.write(esp32.read());
  }
}
