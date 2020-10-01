/*
 * Arduino Workshop - Digipurk OÜ, ylari[at]digipurk.ee
 * Lab 3 - Servo Motor and Ultrasonic Sensor.
 */

#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 12;

Servo servo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  servo.attach(servoPin);
}

void loop() {
  for (int i = 15; i < 165; i++) // rotates the servo motor from 15 to 165 degrees
    send(i);
  for (int i = 165; i > 15; i--) // repeates in the opposite direction
    send(i);
}

void send(int degree) {
  servo.write(degree);
  delay(30);
  Serial.print(degree);
  Serial.print(",");
  Serial.print(distance());
  Serial.print(".");
}

int distance() { // calculates distance measured by the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // sets trigPin high state for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH); // returns the sound wave travel time in microseconds
  return duration * 0.034 / 2; // t * speed of sound / 2
}
