/*
 * Arduino Labs - Digipurk, ylari[at]digipurk.ee
 *
 * AP3216 ambient light and proximity sensor
 * https://digipurk.ee/toode/proximity-light-sensor-wcmcu-3216
 *
 * Connections:
 *   AP3216 -> Arduino
 *     VLED -> 5V
 *     GND  -> GND
 *     VCC  -> 5V
 *     SCL  -> SCL
 *     SDA  -> SDA
 *     INT  -> D2
 */

#include <AP3216_WE.h>
#include <Arduino.h>
#include <Wire.h>

// #define INTERRUPT_MODE

#ifdef INTERRUPT_MODE
#define INTERRUPT 2
volatile bool event = false;
#endif

AP3216_WE sensor;

#ifdef INTERRUPT_MODE
void interrupt() {
  byte type = NO_INT;
  type = sensor.getIntStatus();
  switch (type) {
    case (ALS_INT):
      Serial.println("Ambient light interrupt");
      break;
    case (PS_INT):
      Serial.println("Proximity interrupt");
      break;
    case (ALS_PS_INT):
      Serial.println("Ambient light and proximity interrupt");
      break;
    default:
      Serial.println("Something went wrong ...");
      break;
  }
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  type = sensor.getIntStatus();
  sensor.clearInterrupt(type);
  event = false;
}

void blink() {
  event = true;
}
#endif

void setup() {
#ifdef INTERRUPT_MODE
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(INTERRUPT, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT), blink, FALLING);
#endif
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }
  Wire.begin();
  sensor.init();
  sensor.setLuxRange(RANGE_20661);
  sensor.setIntClearManner(CLR_INT_MANUALLY);
  sensor.setPSThresholds(3, 200);
  sensor.setALSThresholds(3, 500);
  sensor.setPSIntegrationTime(8);
#ifdef INTERRUPT_MODE
  sensor.setPSInterruptMode(INT_MODE_ZONE);
#else
  sensor.setPSInterruptMode(INT_MODE_HYSTERESIS);
#endif
  delay(1000);
}

void loop() {
  float als = sensor.getAmbientLight();
  unsigned int prox = sensor.getProximity();
  unsigned int ir = sensor.getIRData();
#ifndef INTERRUPT_MODE
  bool near = sensor.objectIsNear();
#endif
  bool valid = !sensor.irDataIsOverflowed();
#ifdef INTERRUPT_MODE
  Serial.println("Lux: " + String(als) + "  Proximity: " + String(prox) + "  Infrared: " + String(ir) + "  Valid: " + (valid ? "Yes" : "No"));
#else
  Serial.println("Lux: " + String(als) + "  Proximity: " + String(prox) + "  Object near? " + (near ? "Yes" : "No") + "  Infrared: " + String(ir) + "  Valid: " + (valid ? "Yes" : "No"));
#endif
#ifdef INTERRUPT_MODE
  if (event) {
    interrupt();
  }
#endif
  delay(1000);
}