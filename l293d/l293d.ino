#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);

SoftwareSerial mySerial(9, 10); // Создаем объект SoftwareSerial на пинах 2 (RX) и 3 (TX)

void processCommand(int command) {
  // Устанавливаем максимальную скорость для всех моторов
  int motor_speed = 255;
  motor1.setSpeed(motor_speed);
  motor2.setSpeed(motor_speed);
  motor3.setSpeed(motor_speed);

  // Запускаем моторы в зависимости от команды
switch (command) {
  case '1':
    Serial.println("forward");
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    break;

  case '4':
    Serial.println("backward");
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    break;

  case '2':
    Serial.println("left");
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    break;

  case '3':
    Serial.println("right");
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    break;

  case '5':
    Serial.println("forward left");
    motor1.run(FORWARD);
    motor3.run(BACKWARD);
    break;

  case '6':
    Serial.println("forward right");
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    break;

  case '7':
    Serial.println("backward left");
    motor1.run(BACKWARD);
    motor3.run(FORWARD);
    break;

  case '8':
    Serial.println("backward right");
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    break;

  case '9': 
    Serial.println("stop");
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    break;
  }
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600); // Инициализируем SoftwareSerial на пинах 2 и 3

  // Инициализация моторов и другой начальной настройки
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
}

void loop() {
  if (mySerial.available() > 0) {
    char receivedChar = mySerial.read();
    processCommand(receivedChar);
    Serial.println(receivedChar);
  }
}
