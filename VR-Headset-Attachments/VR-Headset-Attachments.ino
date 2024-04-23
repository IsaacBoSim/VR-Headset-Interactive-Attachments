#include <Servo.h>

Servo servoNape;
Servo servoLeftEar;
Servo servoRightEar;

const int buttonNape = 2;
const int buttonLeftEar = 3;
const int buttonRightEar = 4;
const int buttonFan = 5;
const int buttonStart = 6;

const int servoNapePin = 7;
const int servoLeftEarPin = 8;
const int servoRightEarPin = 9;
const int fanPin = 10;

bool servoNapeState = false;
bool servoLeftEarState = false;
bool servoRightEarState = false;
bool fanState = false;

unsigned long currentTime = 0;

void setup() {
  Serial.begin(9600);

  servoNape.attach(servoNapePin);
  servoLeftEar.attach(servoLeftEarPin);
  servoRightEar.attach(servoRightEarPin);

  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);

  pinMode(buttonNape, INPUT);
  pinMode(buttonLeftEar, INPUT);
  pinMode(buttonRightEar, INPUT);
  pinMode(buttonFan, INPUT);
  pinMode(buttonStart, INPUT);
}

void loop() {
  if (digitalRead(buttonStart) == HIGH) {
    resetTime();
    waitForButtonRelease(buttonStart);
  }

  checkButtonAndToggle(buttonNape, servoNape, servoNapeState);
  checkButtonAndToggle(buttonLeftEar, servoLeftEar, servoLeftEarState);
  checkButtonAndToggle(buttonRightEar, servoRightEar, servoRightEarState);

  if (digitalRead(buttonFan) == HIGH) {
    toggleFan(fanState, buttonFan);
  }

  delay(10);
}

void checkButtonAndToggle(int buttonPin, Servo &servo, bool &state) {
  if (digitalRead(buttonPin) == HIGH) {
    delay(50); // Simple debounce
    state = !state;
    servo.write(state ? 180 : 0);
    printTime();
    printMessage(buttonPin);
    waitForButtonRelease(buttonPin);
    Serial.print(" servo , ");
    Serial.println(state ? "180" : "0");

  }
}

void toggleFan(bool &state, int buttonPin) {
  state = !state;
  digitalWrite(fanPin, state ? HIGH : LOW);
  printTime();
  printMessage(buttonPin);
  Serial.print(" fan , ");
  Serial.println(state ? "HIGH" : "LOW");
  waitForButtonRelease(buttonPin);

}

void resetTime() {
  currentTime = millis();
  printTime();
  Serial.print(0);
  Serial.println(", Starting, Recording");
}

void waitForButtonRelease(int buttonPin) {
  while (digitalRead(buttonPin) == HIGH) {} // Wait for release
}

void printTime(){
  Serial.print(millis() - currentTime);
  Serial.print(", ");
}

void printMessage(int buttonPin){
  Serial.print(String(buttonPin));
  Serial.print(", button toggled");
}