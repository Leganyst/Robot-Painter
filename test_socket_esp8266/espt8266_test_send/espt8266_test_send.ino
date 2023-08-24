#include <SoftwareSerial.h>

SoftwareSerial mySerial(13,15); // Создаем объект SoftwareSerial

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600); // Инициализируем SoftwareSerial на пинах D7 и D8
}

void loop() {
  mySerial.println("Hello from ESP8266!"); // Отправляем данные через SoftwareSerial
  Serial.println("send");
  delay(1000);
}
