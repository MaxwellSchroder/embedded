#include <SoftwareSerial.h>

class Motor {
  private:
    int pinLeft;
    int pinRight;
    String name;
  
  public:
    Motor(int pLeft, int pRight, String n) {
      pinLeft = pLeft;
      pinRight = pRight;
      name = n;
      // establish motor pins as output
      pinMode(pinLeft, OUTPUT);
      pinMode(pinRight, OUTPUT);
      stop();
    }

    turnOnLeft() {
      digitalWrite(pinRight, LOW);
      digitalWrite(pinLeft, HIGH);
    }

    turnOnRight() {
      digitalWrite(pinLeft, LOW);
      digitalWrite(pinRight, HIGH);
    }

    stop() {
      digitalWrite(pinLeft, LOW);
      digitalWrite(pinRight, LOW);
    }
};


class MotorController {
  private:
    Motor motor1;
    Motor motor2;
  
  public:
    MotorController(Motor m1, Motor m2) : motor1(m1), motor2(m2) {
      motor1.stop();
      motor2.stop();
    }

    void controlMotor(String motorName, String command) {
      if (motorName == "motor1") {
        if (command == "left") motor1.turnOnLeft();
        else if (command == "right") motor1.turnOnRight();
        else motor1.stop();
      }
      else if (motorName == "motor2") {
        if (command == "left") motor2.turnOnLeft();
        else if (command == "right") motor2.turnOnRight();
        else motor2.stop();
      }
    }
};





Motor motor1(2, 3, "motor1");
Motor motor2(5, 6, "motor2");

MotorController motorController(motor1, motor2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    Serial.println("hello");
    char incomingChar = Serial.read();

    if (incomingChar == 'L' || incomingChar == 'l') {
      motorController.controlMotor("motor1", "left");
      motorController.controlMotor("motor2", "left");
      Serial.println("Going left on motor 1 and motor 2");
      delay(1000);
    }
    else if (incomingChar == 'R' || incomingChar == 'r') {
      motorController.controlMotor("motor1", "right");
      motorController.controlMotor("motor2", "right");
      Serial.println("Going right on motor 1 and motor 2");
      delay(1000);
    }
    else {
      motorController.controlMotor("motor1", "stop");
      motorController.controlMotor("motor2", "stop");
      Serial.println("Stopping both motor 1 and motor 2");
    }
  }
}
