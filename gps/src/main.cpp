#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial gps(3, 4); // RX, TX

void setup() {
  Serial.begin(9600);
  gps.begin(9600);
}

void loop() {
  if (gps.available()) {
    Serial.write(gps.read());
  }
}
