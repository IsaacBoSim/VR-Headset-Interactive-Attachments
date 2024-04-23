#include <Servo.h>

Servo servoNape, servoLeftEar, servoRightEar;

const int fanPin = 10; // Define the fan pin
const int buttonStart = 6; // Define the start button

void setup() {
  servoNape.attach(7);
  servoLeftEar.attach(8);
  servoRightEar.attach(9);
  pinMode(fanPin, OUTPUT);
  pinMode(buttonStart, OUTPUT);
}

void loop() {
   while (digitalRead(startButton) == LOW) { //wait for start button
       delay(10);
   }
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
