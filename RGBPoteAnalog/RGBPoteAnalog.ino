#define rgb_red_pin 11
#define rgb_green_pin 10
#define rgb_blue_pin 9
#define pot_pin A0

void setup()
{
  pinMode(rgb_red_pin, OUTPUT);
  pinMode(rgb_green_pin, OUTPUT);
  pinMode(rgb_blue_pin, OUTPUT);
}

void loop()
{ 
  int pot_val = analogRead(pot_pin);
  int rgb_val = map(pot_val, 0, 1023, 0, 1535);
  int red;
  int blue;
  int green;
  
  if (rgb_val < 256) {
    red = 255; green = 0; blue = rgb_val;
  }
  else if (rgb_val < 512) {
    red = 511 - rgb_val; green = 0; blue = 255;
  }
  else if (rgb_val < 768) {
    red = 0; green = rgb_val - 512; blue = 255;
  }
  else if (rgb_val < 1024) {
    red = 0; green = 255; blue = 1023 - rgb_val;
  }
  else if (rgb_val < 1280) {
    red = rgb_val - 1024; green = 255; blue = 0;
  }
  else {
    red = 255; green = 1535 - rgb_val; blue = 0;
  }
  
  analogWrite(rgb_red_pin, red);
  analogWrite(rgb_blue_pin, blue);
  analogWrite(rgb_green_pin, green);
}
