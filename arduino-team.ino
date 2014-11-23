#define PIN_LED 13
#define PIN_LED_A 15
#define PIN_LED_B 16
#define PIN_LED_C 17

#define PIN_BTN_1 11
#define PIN_BTN_2 A1

#define PIN_PROXIMITY_LEFT A8
#define PIN_PROXIMITY_BOTTOM A6
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
  Serial.begin(9600);
  while (!Serial) ;

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
}

void loop() {
  if (!digitalRead(PIN_BTN_1)) doRun = true;
  if (!digitalRead(PIN_BTN_2)) doRun = false;

  if (doRun) {
    mirrorProxLed(PIN_PROXIMITY_LEFT, PIN_LED_A);
    mirrorProxLed(PIN_PROXIMITY_BOTTOM, PIN_LED_B);
    mirrorProxLed(PIN_PROXIMITY_RIGHT, PIN_LED_C);

    startMovement(MODE_MOVE_NONE);
  } else {
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);

    if (!digitalRead(PIN_SHARP_CENTER)) {
      startMovement(MODE_MOVE_GO_FORWARD);
    } else {
      startMovement(MODE_MOVE_TURN_RIGHT);
      delay(200);
    }
  }
}

void startMovement(byte mode) {
  startMovement(mode, 127);
}

void startMovement(byte mode, short newPwm) {
  switch (mode) {
    case MODE_MOVE_GO_FORWARD:
      analogWrite(PIN_MOTOR_PWM_LEFT, newPwm);
      digitalWrite(PIN_MOTOR_DIR_LEFT, MOTOR_DIR_LEFT_FORWARD);

      analogWrite(PIN_MOTOR_PWM_RIGHT, newPwm);
      digitalWrite(PIN_MOTOR_DIR_RIGHT, MOTOR_DIR_RIGHT_FORWARD);

      break;
    case MODE_MOVE_GO_BACKWARD:
      analogWrite(PIN_MOTOR_PWM_LEFT, newPwm);
      digitalWrite(PIN_MOTOR_DIR_LEFT, !MOTOR_DIR_LEFT_FORWARD);

      analogWrite(PIN_MOTOR_PWM_RIGHT, newPwm);
      digitalWrite(PIN_MOTOR_DIR_RIGHT, !MOTOR_DIR_RIGHT_FORWARD);

      break;
    case MODE_MOVE_TURN_LEFT:
      analogWrite(PIN_MOTOR_PWM_LEFT, newPwm);
      digitalWrite(PIN_MOTOR_DIR_LEFT, !MOTOR_DIR_LEFT_FORWARD);

      analogWrite(PIN_MOTOR_PWM_RIGHT, newPwm);
      digitalWrite(PIN_MOTOR_DIR_RIGHT, MOTOR_DIR_RIGHT_FORWARD);

      break;
    case MODE_MOVE_TURN_RIGHT:
      analogWrite(PIN_MOTOR_PWM_LEFT, newPwm);
      digitalWrite(PIN_MOTOR_DIR_LEFT, MOTOR_DIR_LEFT_FORWARD);

      analogWrite(PIN_MOTOR_PWM_RIGHT, newPwm);
      digitalWrite(PIN_MOTOR_DIR_RIGHT, !MOTOR_DIR_RIGHT_FORWARD);

      break;
    case MODE_MOVE_NONE:
    default:
      analogWrite(PIN_MOTOR_PWM_LEFT, 0);
      digitalWrite(PIN_MOTOR_DIR_LEFT, MOTOR_DIR_LEFT_FORWARD);

      analogWrite(PIN_MOTOR_PWM_RIGHT, 0);
      digitalWrite(PIN_MOTOR_DIR_RIGHT, MOTOR_DIR_RIGHT_FORWARD);

      break;
  }
}

void mirrorProxLed(short sensorPin, short ledPin) {
  digitalWrite(ledPin, analogRead(sensorPin) < 200 ? HIGH : LOW);
}

