/*
 * Arduino Labs - Digipurk, ylari[at]digipurk.ee
 *
 * L9110 motor driver
 * https://digipurk.ee/toode/fan-module-l9110
 *
 * Connections:
 *   L9110 -> Arduino
 *     INA -> D5
 *     INB -> D6
 *     VCC -> 5V
 *     GND -> GND
 */

#include <Arduino.h>

const int INA = 5;
const int INB = 6;

void stopMotor() {
  analogWrite(INA, 0);
  analogWrite(INB, 0);
}

void brakeMotor() {
  analogWrite(INA, 255);
  analogWrite(INB, 255);
}

void setMotor(int speed) {
  speed = constrain(speed, -255, 255);
  if (speed > 0) {
    analogWrite(INA, speed);
    analogWrite(INB, 0);
  } else if (speed < 0) {
    analogWrite(INA, 0);
    analogWrite(INB, -speed);
  } else {
    stopMotor();
  }
}

void rampTo(int target, int stepDelayMs = 10) {
  static int cur = 0;
  int step = (target > cur) ? 1 : -1;
  while (cur != target) {
    cur += step;
    setMotor(cur);
    delay(stepDelayMs);
  }
}

void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  stopMotor();
}
void loop() {
  rampTo(200);
  delay(1500);
  rampTo(0);
  delay(200);
  rampTo(-200);
  delay(1500);
  rampTo(0);
  delay(800);
}
