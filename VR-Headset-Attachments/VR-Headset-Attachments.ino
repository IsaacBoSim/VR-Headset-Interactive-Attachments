#include <Servo.h>

Servo servoNape;
Servo servoThroat;
Servo servoLeftEar;
Servo servoRightEar;

const int servoNapePin = 6;
const int servoThroatPin = 7;
const int servoLeftEarPin = 8;
const int servoRightEarPin = 9;
const int fanPin = 10;

const int buttonNape = 2;
const int buttonThroat = 3;
const int buttonLeftEar = 4;
const int buttonRightEar = 5;
const int buttonFan = 6;
const int buttonStart = 7;

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
    waitForButtonRelease(buttonStart);
  }

  checkButtonAndToggle(buttonNape, servoNape, servoNapeState);
  checkButtonAndToggle(buttonThroat, servoThroat, servoThroatState);
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
    Serial.println("Servo at pin " + String(buttonPin) + " toggled");
    waitForButtonRelease(buttonPin);
  }
}

void toggleFan(bool &state, int buttonPin) {
  state = !state;
  digitalWrite(fanPin, state ? HIGH : LOW);
  Serial.println("Fan Toggled");
  waitForButtonRelease(buttonPin);
}

void resetTime() {
  currentTime = millis();
  printTime();
  Serial.println("Starting Record");
}

void waitForButtonRelease(int buttonPin) {
  while (digitalRead(buttonPin) == HIGH) {} // Wait for release
}

void printTime(){
  Serial.print(millis() - currentTime);
  Serial.print(" s ");
}