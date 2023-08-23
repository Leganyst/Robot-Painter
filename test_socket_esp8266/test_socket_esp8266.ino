#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include "test.h"

// Настройки Wi-Fi
const char* ssid = "SKBKIT_205";
const char* password = "skbkit2020";

// Создаем объекты для веб-сервера и веб-сокета
ESP8266WebServer server(80);
WebSocketsServer webSocket(81);



//uint8_t num: Это номер клиента (соединения), для которого произошло событие. При работе с веб-сокетами может быть несколько одновременных соединений, и каждое соединение получает свой уникальный номер (индекс). 
//Этот номер представляет собой индекс внутреннего массива клиентов библиотеки.
//WStype_t type: Это тип события, которое произошло. В данном случае, код сравнивается с WStype_TEXT, что означает, что произошло событие получения текстового сообщения.
//uint8_t *payload: Это указатель на массив байт, который содержит данные, переданные по веб-сокету. В данном случае, это текстовое сообщение, которое вы отправили по сети.
//size_t length: Это длина полученных данных в байтах. Она указывает на количество байтов в массиве payload, которые являются действительными данными.
// Обработчик событий веб-сокета
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      // При получении текстового сообщения
      Serial.printf("[%u] Received text: %s\n", num, payload);
      break;
  }
}

void setup() {
  Serial.begin(115200);

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

void loop() {
  // Обработка клиентских запросов и событий веб-сокета
  server.handleClient();
  webSocket.loop();
}
