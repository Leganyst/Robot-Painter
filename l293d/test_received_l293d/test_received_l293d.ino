#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10); // Создаем объект SoftwareSerial на пинах 2 (RX) и 3 (TX)

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600); // Инициализируем SoftwareSerial на пинах 2 и 3
}

void loop() {
  if (mySerial.available() > 0) {
    char receivedChar = mySerial.read();
    Serial.println(receivedChar);
  }
}
