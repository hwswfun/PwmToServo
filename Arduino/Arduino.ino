#include <Servo.h>

// These constants won't change. They're used to give names to the pins used:
const int m1Black = A0;  // Analog input pin that the potentiometer is attached to
const int m1Red = A1;
const int m2Black = A2;  // Analog input pin that the potentiometer is attached to
const int m2Red = A3;


int m1ServoOut = 90;

Servo leftServo;  // create servo object to control a servo
Servo rightServo;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  leftServo.attach(8);
  rightServo.attach(9);
}

void loop() {
  float m1Value = readStick(m1Black, m1Red);
  float m2Value = readStick(m2Black, m2Red);

  int sLeft = 90 + 15 * m1Value;
  Serial.print(sLeft);
  leftServo.write(sLeft);

  int sRight = 90 + -15 * m2Value;  // instead of 15, can go about 40 to allow full speed.  this way it is limited.
  Serial.println("\t"+sRight);
  rightServo.write(sRight);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(20);
}

float readStick(int blackAnalogPin, int redAnalogPin) {
  // read the analog in value:
  int blackValue = analogRead(blackAnalogPin);
  int redValue = analogRead(redAnalogPin);
  float ret=0.0f;

 if (blackValue > 600) {
    // forward
    ret = map(redValue, 0, 250, 1000, 0) / 1000.0f;
  } else if (redValue >600) {
    // backward
    ret = map(blackValue, 0, 250, -1000, 0) / 1000.0f;
  } else ret = 0.0f;
  return ret;  
}



/*
 * For motor 1.  2 analog inputs because monitor red and black wire independantly.
                A0 (black)    A1 (red)
full up         678           0
above neutral - 678           237
Neutral -       0             0
below neutral - 247           665
full down -     0             665

  m1BlackValue = analogRead(m1Black);
  m1RedValue = analogRead(m1Red);



*/


