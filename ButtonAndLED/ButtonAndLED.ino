/*
 * Arduino Workshop - Digipurk OÜ, ylari[at]digipurk.ee
 * Lab 1 - Push Button and LED
 */

// constants
const int buttonPin = 7;
const int ledPin =  6;
const int photoRPin = A0; // analog pin A0

// variables
int buttonState = 0;
int flag = 0;
String input = ""; // a string to hold incoming data
bool automatic = false;
bool complete = false; // whether the string is complete
int value; // store value from photoresistor (0 - 1023)

// The setup function runs once when you press reset or power the board.
void setup() {
  Serial.begin(9600); // start serial port
  input.reserve(128); // reserve 200 bytes for serial input
  // input or output?
  pinMode(LED_BUILTIN, OUTPUT); // digital pin 13
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(photoRPin, INPUT);
}

// The loop function runs over and over again forever.
void loop() {
  if (complete)
    Serial.println("INPUT: " + input); // debug message
  if (input.equalsIgnoreCase("switch")) {
    Serial.print("AUTOMATIC: ");
    Serial.println(automatic ? "off" : "on");
    automatic = !automatic;
  }
  if (automatic) {
    value = analogRead(photoRPin);
    Serial.println("VALUE: " + String(value));
    if (value < 700) {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED: on");
    } else {
      digitalWrite(ledPin, LOW);
      Serial.println("LED: off");
    }
  } else {
    // read button state (pressed or not pressed?)
    buttonState = digitalRead(buttonPin);
    // if button pressed ...
    if (buttonState == HIGH || input.equalsIgnoreCase("led")) {
      // ... once, turn led on!
      if (flag == 0) {
        digitalWrite(ledPin, HIGH);
        Serial.println("LED: on");
        flag = 1; // change flag variable
      }
      // ... twice, turn led off!
      else if (flag == 1) {
        digitalWrite(ledPin, LOW);
        Serial.println("LED: off");
        flag = 0; // change flag variable again
      }
    }
  }
  if (complete) {
    input = ""; // clear input
    complete = false;
  }
  delay(500); // small delay
}

/*
 * SerialEvent occurs whenever a new data comes in the hardware serial RX. This
 * routine is run between each time loop() runs, so using delay inside loop can
 * delay response. Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    char in = (char) Serial.read(); // get the new byte
    if (in != '\n')
      input += in; // add it to the input
    else // if the incoming character is a newline, set a flag so the main loop can do something about it
      complete = true;
  }
}
