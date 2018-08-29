#include <Servo.h>

/*
Converts DC H-Bridge motor controller output to a hobby ESC control.
1.Simulates a DC motor with a resistor divider
2.Measures voltage on both leads on the DC motor
3.Determines % of power intended to drive the motor
4.Sets the positions the Servo responsible for that motor's ESC.

Created by Nathan Tofte (HWSWFUN)
August 28, 2018
*/

const int motor1Black = A0;   // Analog input pin for black wire of motor 1
const int motor1Red = A1;     // Analog input pin for red wire of motor 1
const int motor2Black = A2;   // Analog input pin for black wire of motor 2
const int motor2Red = A3;     // Analog input pin for red wire of motor 2

const int motor1ESC = D8;     // Pin connected to ESC for motor 1
const int motor2ESC = D9;     // Pin connected to ESC for motor 2

Servo motor1ESC;  // Servo output for motor 1.  Connect to motor 1 Electronic Speed Control.
Servo motor2ESC;  // Servo output for motor 1.  Connect to motor 1 Electronic Speed Control.

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  motor1ESC.attach(motor1ESC);
  motor2ESC.attach(motor2ESC);
}

int fullSpeedOffset = 45; // Add to 90 to get full speed
int speedScale = 3;       // Hobby motor can be super fast so scale the speed to only a portion.

void loop() {
  float motor1Value = readStick(motor1Black, motor1Red);
  float motor2Value = readStick(motor2Black, motor2Red);

  int sLeft = 90 + (fullSpeedOffset / speedScale) * motor1Value;
  Serial.print(sLeft);
  motor1ESC.write(sLeft);

  int sRight = 90 + -(fullSpeedOffset / speedScale) * motor2Value;
  Serial.println("\t"+sRight);
  motor2ESC.write(sRight);

  // wait 20 milliseconds before the next loop for the analog-to-digital
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
2 analog inputs to monitor red and black wires independantly.
These are sample A/D readings

                      A0 (black)    A1 (red)
full up               678           0
just above neutral -  678           237
Neutral -             0             0
just below neutral -  247           665
full down -           0             665
*/
