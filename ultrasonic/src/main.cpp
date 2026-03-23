/*
 * Arduino Labs - Digipurk, ylari[at]digipurk.ee
 *
 * Ultrasonic distance measurement with HC-SR04 sensor
 * https://digipurk.ee/toode/ultraheliandur
 *
 * Connections:
 *   HC-SR04 -> Arduino
 *      TRIG -> D10
 *      ECHO -> D11
 *      VCC -> 5V
 *      GND -> GND
 */

#include <Arduino.h>

#define TRIGGER 10
#define ECHO 11

float distance();

float average = 0;

void setup() {
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int count = 0;
  for (int i = 0; i < 5; i++) {
    float tmp = distance();
    if (tmp != 0 && tmp < 300) {
      average += tmp;
      count++;
    }
    delay(10);
  }
  if (count > 0 && average > 0) {
    average /= count;
    Serial.print(average);
    Serial.println(" cm");
  }
  average = 0;
}

float distance() {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  long duration = pulseIn(ECHO, HIGH, 250000);
  return duration * 0.0343 / 2;
}