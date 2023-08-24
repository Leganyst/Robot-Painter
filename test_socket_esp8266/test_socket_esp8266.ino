#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

#include "test.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(13,15); // Создаем объект SoftwareSerial

// Настройки Wi-Fi
const char* ssid = "SKBKIT_205";
const char* password = "skbkit2020";

// Создаем объекты для веб-сервера и веб-сокета
ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600); // Инициализируем SoftwareSerial на пинах D7 и D8
  
  // Подключение к Wi-Fi сети
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  
  // Настройка маршрутов веб-сервера
  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", htmlPage);
  });

  // Запуск веб-сервера и веб-сокета
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      // При получении текстового сообщения по веб-сокету
      String data = (char*)payload;
      mySerial.println(data); // Отправляем данные через SoftwareSerial
      Serial.println(data);
      break;
  }
}

void loop() {
  // Обработка клиентских запросов и событий веб-сокета
  server.handleClient();
  webSocket.loop();
}
