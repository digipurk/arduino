/*
 * Arduino Workshop - Digipurk OÜ, ylari[at]digipurk.ee
 * Lab 2 - RGB LED and Temperature
 */

#include <OneWire.h> // first we include the libraries
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 // data wire is plugged into pin 2

OneWire oneWire(ONE_WIRE_BUS); // setup oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // pass our oneWire reference to Dallas Temperature

#define RED_PIN 11
#define GREEN_PIN 9
#define BLUE_PIN 10

int green = 255, red = 0; // variables

void setLED(int green, int red) {
  analogWrite(GREEN_PIN, green);
  analogWrite(RED_PIN, red);
}

void setup(void) {
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  Serial.begin(9600); // start serial port
  Serial.println("Dallas Temperature IC Control Library Demo");
  sensors.begin(); // start up the library
  for (int i = 0; i < 255; i++) {
    setLED(255 - i, i);
    delay(20);
  }
}

void loop(void) {
  Serial.print(" Requesting temperatures ..."); // call sensors.requestTemperatures() to issue a global temperature request to all devices on the bus
  sensors.requestTemperatures(); // send the command to get temperature readings
  Serial.println(" DONE");
  Serial.print("Temperature is ");
  float temp = sensors.getTempCByIndex(0); // why "byIndex"? you can have more than one DS18B20 on the same bus. 0 refers to the first IC on the wire
  Serial.print(temp);
  Serial.println(" °C");
  if (temp <= 28.00 && temp > 25.00) { // max and min limits
    red = map((int) (temp * 100), 2500, 2800, 0, 255);
    green = 255 - red;
  }
  setLED(green, red);
  delay(10);
}
