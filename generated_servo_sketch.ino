#include <Servo.h>

Servo servoLeftEar, servoRightEar;

const int fanPin = 10; // Define the fan pin
const int startButton = 6; // Define the start button

void setup() {
  servoLeftEar.attach(7);
  servoRightEar.attach(8);
  pinMode(fanPin, OUTPUT);
  pinMode(startButton, INPUT);
  digitalWrite(fanPin, LOW);
}

void loop() {
  while (digitalRead(startButton) == LOW) { //wait for start button
    if (digitalRead(startButton) == HIGH){
      Serial.print("Starting Recording");
      break;
    }
  }
  delay(0);
  delay(1208);
  digitalWrite(fanPin, HIGH);
  delay(2966);
  servoLeftEar.write(180);
  delay(8855);
  servoRightEar.write(180);
  delay(3234);
  servoRightEar.write(0);
  delay(5502);
  servoRightEar.write(180);
  delay(6699);
  servoLeftEar.write(0);
  delay(13642);
  servoRightEar.write(0);
  delay(857);
  servoRightEar.write(180);
  end();
}

void end() {
  digitalWrite(fanPin, LOW);
  Serial.println("Ended Recording");
}
