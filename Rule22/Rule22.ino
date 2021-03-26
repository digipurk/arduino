/*
 * Arduino Day 2021 - Digipurk OÜ, ylari[at]digipurk.ee
 * 2 + 2 Rule implementation using and Ultrasonic Sensor.
 */

#define LED_RED 6
#define LED_YELLOW 5
#define LED_GREEN 3

#define BUZZER 9

#define TRIGGER 10
#define ECHO 11

float average = 0;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
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
    if (average < 250 && average >= 200)
      yellow();
    else if (average < 200 && average > 0)
      red();
    else
      green();
    Serial.print(average);
    Serial.println(" cm");
  } else {
    Serial.println("Ohtu pole :)");
    green();
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
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  tone(BUZZER, 4000);
}

void yellow() {
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  noTone(BUZZER);
}

void green() {
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  noTone(BUZZER);
}
