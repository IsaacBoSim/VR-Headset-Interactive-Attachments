#include <Servo.h>

Servo servoNape;
Servo servoThroat;
Servo servoLeftEar;
Servo servoRightEar;

const int servoNapePin = 3;
const int servoThroatPin = 5;
const int servoLeftEarPin = 6;
const int servoRightEarPin = 9;
const int fanPin = 11;

const int buttonNape = 2;
const int buttonThroat = 4;
const int buttonLeftEar = 7;
const int buttonRightEar = 8;
const int buttonFan = 10;
const int buttonStart = 12;

bool servoNapeState = false;
bool servoThroatState = false;
bool servoLeftEarState = false;
bool servoRightEarState = false;
bool fanState = false;

unsigned long currentTime = 0;

void setup() {
  Serial.begin(9600);

  servoNape.attach(servoNapePin);
  servoThroat.attach(servoThroatPin);
  servoLeftEar.attach(servoLeftEarPin);
  servoRightEar.attach(servoRightEarPin);

  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);

  pinMode(buttonNape, INPUT);
  pinMode(buttonThroat, INPUT);
  pinMode(buttonLeftEar, INPUT);
  pinMode(buttonRightEar, INPUT);
  pinMode(buttonFan, INPUT);
  pinMode(buttonStart, INPUT);
}

void loop() {
  if (digitalRead(buttonStart) == HIGH) {
    resetTime();
  }

  if (digitalRead(buttonNape) == HIGH) {
    toggleServo(servoNape, servoNapeState, buttonNape);
    Serial.println("Nape Servo Activated");
  }

  if (digitalRead(buttonThroat) == HIGH) {
    toggleServo(servoThroat, servoThroatState, buttonThroat);
    Serial.println("Throat Servo Activated");
  }

  if (digitalRead(buttonLeftEar) == HIGH) {
    toggleServo(servoLeftEar, servoLeftEarState, buttonLeftEar);
    Serial.println("Left Ear Servo Activated");
  }

  if (digitalRead(buttonRightEar) == HIGH) {
    toggleServo(servoRightEar, servoRightEarState, buttonRightEar);
    Serial.println("Right Ear Servo Activated");
  }

  if (digitalRead(buttonFan) == HIGH) {
    toggleFan(fanState, buttonFan);
    Serial.println("Fan Toggled");
  }
}

void toggleServo(Servo &servo, bool &state, int buttonPin) {
  state = !state;
  servo.write(state ? 180 : 0);
  buttonRelease(buttonPin);
}

void toggleFan(bool &state, int buttonPin) {
  state = !state;
  digitalWrite(fanPin, state ? HIGH : LOW);
  buttonRelease(buttonPin);
}

void resetTime() {
  currentTime = millis();
  Serial.println("Starting Record");
}

void buttonRelease(int buttonPin) {
  while (digitalRead(buttonPin) == HIGH) {
  }
  delay(10);
}
