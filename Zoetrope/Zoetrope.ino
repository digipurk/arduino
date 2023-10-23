/*
 * Zoetrope - Digipurk OÜ, ylari[at]digipurk.ee
 */

#include <Servo.h> 
Servo myservo;    
 
void setup() {
  myservo.attach(9); 
  Serial.begin(9600);
} 
 
void loop() {
  int analogValue = analogRead(A0);
  int speed_min = 84;
  int speed_max = 180;
  int map_val = map(analogValue,0,1023,speed_min,speed_max);

  Serial.println(map_val);
  myservo.write(map_val);
}
