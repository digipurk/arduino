/*
 * Arduino Labs - Digipurk, ylari[at]digipurk.ee
 *
 * Barrier workshop
 */

#include <Arduino.h>
#include <IRremote.h>
#include <Servo.h>

#define RED 6
#define YELLOW 5
#define GREEN 3

#define TRIGGER 10
#define ECHO 11

#define SERVO 9

#define IR 7

#define UP 70
#define DOWN 150

float average = 0;
bool isUp = false;

Servo servo;

float distance();
void red();
void yellow();
void green();
void up();
void down();

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT_PULLUP);
  servo.attach(SERVO);
  IrReceiver.begin(IR, ENABLE_LED_FEEDBACK);
  servo.write(DOWN);
  red();
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
    if (average < 20) {
      if (!isUp) {
        Serial.println("UP");
        up();
      }
      green();
    } else {
      if (isUp) {
        Serial.println("DOWN");
        down();
      }
      red();
    }
  }

  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.decodedRawData == 0xE718FF00) {
      if (!isUp) {
        Serial.println("UP");
        up();
      }
      green();
    }
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    IrReceiver.resume();
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

void red() {
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
}

void yellow() {
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, LOW);
}

void green() {
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
}

void up() {
  yellow();
  for (int i = DOWN; i >= UP; i--) {
    servo.write(i);
    delay(15);
  }
  isUp = true;
}

void down() {
  unsigned long start = millis();
  while (millis() - start < 10000) {
    if (IrReceiver.decode()) {
      if (IrReceiver.decodedIRData.decodedRawData == 0xAD52FF00) {
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
        break;
      }
      IrReceiver.resume();
    }
  }
  yellow();
  for (int i = UP; i < DOWN; i++) {
    servo.write(i);
    delay(15);
  }
  isUp = false;
}