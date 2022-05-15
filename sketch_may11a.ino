#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <stdio.h>
#include <stdlib.h>
#include <DHT.h>

#define DHTTYPE DHT22

SoftwareSerial esp32(2,3);
DHT dht(13, DHTTYPE);
LiquidCrystal lcd(4,5,8,9,10,11);

void cmdtest(){
  esp32.println("AT");

  if(esp32.find("OK")){
    Serial.println("Test Success");
  }else if(esp32.find("ERROR")){
    Serial.println("Test Error");
  }
}

void wifitest(){
  esp32.println("AT+CWSTATE?");
  
  if(esp32.find("2")){
    Serial.println("Wifi Conncected");
  }else{
    Serial.println("Wifi Error");
  }
}

void httpclient(String ch1, String ch2){
  String cmd = "AT+HTTPCLIENT=3,3,";
  cmd += "\"http://52.192.183.203\"";
  cmd += ",,,1,";
  cmd += "\"CH1=";
  cmd += ch1;
  cmd += "&CH2=";
  cmd += ch2;
  cmd += "\"";
  esp32.println(cmd);
}

void setup() {
  dht.begin();
  lcd.begin(16,2);
  Serial.begin(115200);
  esp32.begin(115200);
  cmdtest();
  wifitest();
}

void loop() {
  delay(300);
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  char x[16];
  
  String strHumi = dtostrf(humi,4,1,x);
  String strTemp = dtostrf(temp,4,1,x);
  
  lcd.setCursor(0,0);
  lcd.print("Humi:");
  lcd.setCursor(6,0);
  lcd.print(strHumi);
  lcd.setCursor(11,0);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.setCursor(6,1);
  lcd.print(strTemp);
  lcd.setCursor(11,1);
  lcd.print("*C");

  delay(500);
  httpclient(strTemp, strHumi);
  delay(500);

  while (esp32.available()){
    Serial.write(esp32.read());
  }
  delay(2000);
}
