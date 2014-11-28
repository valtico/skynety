#define PIN_LED_A 15
#define PIN_LED_B 16
#define PIN_LED_C 17

#define PIN_BTN_1 11
#define PIN_BTN_2 A1

#define PIN_PROXIMITY_LEFT A8
#define PIN_PROXIMITY_BACK A6
#define PIN_PROXIMITY_RIGHT A4

#define PIN_SHARP_LEFT 7
#define PIN_SHARP_CENTER A3
#define PIN_SHARP_RIGHT A5

#define PIN_MOTOR_LEFT_A 5
#define PIN_MOTOR_LEFT_B 6
#define PIN_MOTOR_RIGHT_A 10
#define PIN_MOTOR_RIGHT_B 9

#ifndef DO_USE_SERIAL
#define DO_USE_SERIAL 0
#endif

boolean doRun = false;

boolean didWaitFiveSeconds = false;

void setup() {
#if DO_USE_SERIAL
  // set up Serial
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("hello world.");
#endif /* DO_USE_SERIAL */

  // set up LEDs
  pinMode(PIN_LED_A, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_C, OUTPUT);

  // set up buttons
  pinMode(PIN_BTN_1, INPUT_PULLUP);
  pinMode(PIN_BTN_2, INPUT_PULLUP);

  // set up floor sensors
  pinMode(PIN_PROXIMITY_LEFT, INPUT);
  pinMode(PIN_PROXIMITY_BACK, INPUT);
  pinMode(PIN_PROXIMITY_RIGHT, INPUT);

  // set up enemy sensors
  pinMode(PIN_SHARP_LEFT, INPUT);
  pinMode(PIN_SHARP_CENTER, INPUT);
  pinMode(PIN_SHARP_RIGHT, INPUT);

  // set up motors
  pinMode(PIN_MOTOR_LEFT_A, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_B, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_A, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_B, OUTPUT);
}

void loop() {
  if (!doRun) if (!digitalRead(PIN_BTN_1)) doRun = true; // doRun was false and btn 1 was pushed
  if (doRun) if (!digitalRead(PIN_BTN_2)) doRun = false; // doRun was true and btn 2 was pushed

  if (!doRun) {
    // abort; either the kill switch's been pressed or we just haven't initialized yet
    didWaitFiveSeconds = false;

    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);

    goForward(0, 0);
  } else {
    if (!didWaitFiveSeconds) {
      delay(5000);
      didWaitFiveSeconds = true;
    }

    int motorState = 0;
    
    if (!digitalRead(PIN_SHARP_LEFT)) {
      motorState += 8;
    }
    if (!digitalRead(PIN_SHARP_CENTER)) {
      motorState += 16;
    }
    if (!digitalRead(PIN_SHARP_RIGHT)) {
      motorState += 32;
    }
    
    if (motorState == 0) {
      if (analogRead(PIN_PROXIMITY_LEFT) < 150) {
        motorState += 1;
        digitalWrite(PIN_LED_A, HIGH);
      } else digitalWrite(PIN_LED_A, LOW);
      if (analogRead(PIN_PROXIMITY_RIGHT) < 150) {
        motorState += 2;
        digitalWrite(PIN_LED_B, HIGH);
      } else digitalWrite(PIN_LED_B, LOW);
      if (analogRead(PIN_PROXIMITY_BACK) < 150) {
        motorState += 4;
        digitalWrite(PIN_LED_C, HIGH);
      } else digitalWrite(PIN_LED_C, LOW);
    }

    switch(motorState) {
    case 0: // nothing nowhere
      goRight(150, 150);
      delay(10);
      break;
    case 1:
      goRight(200, 200);
      delay(300);
      break;
    case 2:
      goLeft(200, 200);
      delay(300);
      break;
    case 3:
      goBackwards(200, 200);
      delay(200);
      break;
    case 4:
      goForward(200, 200);
      delay(300);
      break;
    case 5:
      goForward(250, 250);
      delay(200);
      goRight(200, 200);
      delay(100);
      break;
    case 6:
      goForward(250, 250);
      delay(200);
      goLeft(200, 200);
      delay(100);
      break;
    case 7:
      goForward(0, 0);
      delay(10);
      break;
    case 8: // sharp left
      goLeft(200, 200);
      delay(10);
      break;
    case 16: // sharp center
      goForward(250, 250);
      delay(10);
      break;
    case 24: // sharp left + center
      goForward(200, 250);
      delay(10);
      break;
    case 32: // sharp right
      goRight(200, 200);
      delay(10);
      break;
    case 48: // sharp center + right
      goForward(250, 200);
      delay(10);
      break;
    case 40: // sharp left + right
    case 56: // sharp left + center + right
      goForward(250, 250);
      delay(10);
      break;
    }
  }
}

void goForward(int leftSpeed, int rightSpeed) {
  analogWrite(PIN_MOTOR_LEFT_A, leftSpeed);
  digitalWrite(PIN_MOTOR_LEFT_B, LOW);
  analogWrite(PIN_MOTOR_RIGHT_A, rightSpeed);
  digitalWrite(PIN_MOTOR_RIGHT_B, LOW);
}

void goBackwards(int leftSpeed, int rightSpeed) {
  analogWrite(PIN_MOTOR_LEFT_B, leftSpeed);
  digitalWrite(PIN_MOTOR_LEFT_A, LOW);
  analogWrite(PIN_MOTOR_RIGHT_B, rightSpeed);
  digitalWrite(PIN_MOTOR_RIGHT_A, LOW);
}

void goLeft(int leftSpeed, int rightSpeed) {
  analogWrite(PIN_MOTOR_LEFT_B, leftSpeed);
  digitalWrite(PIN_MOTOR_LEFT_A, LOW);
  analogWrite(PIN_MOTOR_RIGHT_A, rightSpeed);
  digitalWrite(PIN_MOTOR_RIGHT_B, LOW);
}

void goRight(int leftSpeed, int rightSpeed) {
  analogWrite(PIN_MOTOR_LEFT_A, leftSpeed);
  digitalWrite(PIN_MOTOR_LEFT_B, LOW);
  analogWrite(PIN_MOTOR_RIGHT_B, rightSpeed);
  digitalWrite(PIN_MOTOR_RIGHT_A, LOW);
}

