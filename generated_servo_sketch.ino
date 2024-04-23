#include <Servo.h>

Servo servoNape, servoThroat, servoLeftEar, servoRightEar;

const int fanPin = 10; // Define the fan pin
void setup() {
  servoNape.attach(6);
  servoThroat.attach(7);
  servoLeftEar.attach(8);
  servoRightEar.attach(9);
  pinMode(fanPin, OUTPUT);
}

void loop() {
  delay(0);
  delay(2331);
  digitalWrite(10, HIGH);
  delay(3125);
  servoRightEar.write(180);
  delay(1918);
  digitalWrite(10, LOW);
  delay(2369);
  servoRightEar.write(0);
  while(true); // Stop further actions
}
