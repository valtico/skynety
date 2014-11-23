#define PIN_LED 13
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

#define PIN_MOTOR_PWM_LEFT 5
#define PIN_MOTOR_DIR_LEFT 6
#define PIN_MOTOR_PWM_RIGHT 10
#define PIN_MOTOR_DIR_RIGHT 9

#define MOTOR_DIR_LEFT_FORWARD LOW
#define MOTOR_DIR_RIGHT_FORWARD LOW

#define MODE_MOVE_NONE 1
#define MODE_MOVE_GO_FORWARD 2
#define MODE_MOVE_GO_BACKWARD 3
#define MODE_MOVE_TURN_LEFT 4
#define MODE_MOVE_TURN_RIGHT 5

boolean doRun = false;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LED_A, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_C, OUTPUT);

  pinMode(PIN_BTN_1, INPUT_PULLUP);
  pinMode(PIN_BTN_2, INPUT_PULLUP);

  pinMode(PIN_PROXIMITY_LEFT, INPUT);
  pinMode(PIN_PROXIMITY_BOTTOM, INPUT);
  pinMode(PIN_PROXIMITY_RIGHT, INPUT);

  pinMode(PIN_SHARP_LEFT, INPUT);
  pinMode(PIN_SHARP_CENTER, INPUT);
  pinMode(PIN_SHARP_RIGHT, INPUT);

  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_DIR_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);
  pinMode(PIN_MOTOR_DIR_RIGHT, OUTPUT);
}

void loop() {
  if (!digitalRead(PIN_BTN_1)) doRun = true;
  if (!digitalRead(PIN_BTN_2)) doRun = false;

  if (doRun) {
    int motorState = 0;

    if (isCloseToSensor(PIN_PROXIMITY_LEFT)) {
      motState += 1;
      digitalWrite(PIN_LED_A, HIGH);
    } else digitalWrite(PIN_LED_A, LOW);

    if (isCloseToSensor(PIN_PROXIMITY_RIGHT)) {
      motState += 2;
      digitalWrite(PIN_LED_B, HIGH);
    } else digitalWrite(PIN_LED_B, LOW);

    if (isCloseToSensor(PIN_PROXIMITY_BACK)) {
      motState += 4;
      digitalWrite(PIN_LED_C, HIGH);
    } else digitalWrite(PIN_LED_C, LOW);

    switch(motorState) {
    case 0:
      goLeft(100, 100);
      break;
    case 1:
      goRight(100, 100);
      delay(300);
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    }

    if (digitalRead(PIN_SHARP_CENTER)) {
      goForward(150, 150);
    } else {
      goRight(150, 150);
    }
    delay(500);
  } else {
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);
  }
}

void goForward(int leftSpeed, int rightSpeed) {
  analogWrite(5, leftSpeed);
  digitalWrite(6, LOW);
  analogWrite(10, rightSpeed);
  digitalWrite(9, LOW);
}

void goBackwards(int leftSpeed, int rightSpeed) {
  analogWrite(6, leftSpeed);
  digitalWrite(5, LOW);
  analogWrite(9, rightSpeed);
  digitalWrite(10, LOW);
}

void goLeft(int leftSpeed, int rightSpeed) {
  analogWrite(6, leftSpeed);
  digitalWrite(5, LOW);
  analogWrite(10, rightSpeed);
  digitalWrite(9, LOW);
}

void goRight(int leftSpeed, int rightSpeed) {
  analogWrite(5, leftSpeed);
  digitalWrite(6, LOW);
  analogWrite(9, rightSpeed);
  digitalWrite(10, LOW);
}

boolean isCloseToSensor(int sensorPin) {
  return analogRead(sensorPin) < 200;
}

