//주변환경의 온도와 습도를 측정하여 시리얼모니터에 출력하기
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 8
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  dht.begin();

}

void loop() {
  //온도와 습도 값을 측정하고 변수에 저장하기
  float humi, temp;
  temp = dht.readTemperature();
  humi = dht.readHumidity();

  //센서가 측정하지 못 할 경우 측정 종료
  if(isnan(humi) || isnan(temp)){
    Serial.println("Failed to read from DHT sensor!!");
    return;
  }

//측정된 온도와 습도 출력하기
Serial.print("온도 : ");
Serial.print(temp);
Serial.println("ºC");
Serial.print("습도 : ");
Serial.print(humi);
Serial.println("%");
delay(300);

}
