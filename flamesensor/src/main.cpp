/*
 * Arduino Labs - Digipurk, ylari[at]digipurk.ee
 *
 * Flame sensor (phototransistor)
 * https://digipurk.ee/toode/infrared-receiver-diode-5-mm
 *
 * Connections:
 *   VCC
 *   |
 *   [resistor 10k]
 *   |
 *   OUT -----> Arduino (A0)
 *   |
 *   (collector)
 *   Phototransistor
 *   (emitter)
 *   |
 *   GND
 */

#include <Arduino.h>

#define FLAMESENSOR A0

void setup() {
  pinMode(FLAMESENSOR, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(FLAMESENSOR);
  int range = map(value, 0, 1024, 0, 3);
  switch (range) {
    case 0:
      Serial.println("Fire");
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    case 1:
      Serial.println("Flame is nearby");
      break;
    case 2:
      Serial.println("No flame detected");
      digitalWrite(LED_BUILTIN, LOW);
      break;
    default:
      break;
  }
  delay(500);
}