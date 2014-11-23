#define PIN_LED 13
#define PIN_LED_A 15
#define PIN_LED_B 16
#define PIN_LED_C 17

#define PIN_BTN_1 11
#define PIN_BTN_2 A1

#define PIN_DIP_SWITCH_1 0
#define PIN_DIP_SWITCH_2 1
#define PIN_DIP_SWITCH_3 2
#define PIN_DIP_SWITCH_4 3

#define PIN_PROXIMITY_LEFT A8
#define PIN_PROXIMITY_BOTTOM A6
#define PIN_PROXIMITY_RIGHT A4

boolean doRun = false;

void setup() {
  Serial.begin(9600);
  while (!Serial) ;

  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_BTN_1, INPUT_PULLUP);
  pinMode(PIN_BTN_2, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(PIN_BTN_1)) doRun = true;
  if (!digitalRead(PIN_BTN_2)) doRun = false;

  if (doRun) {
    mirrorProxLed(PIN_PROXIMITY_LEFT, PIN_LED_A);
    mirrorProxLed(PIN_PROXIMITY_BOTTOM, PIN_LED_B);
    mirrorProxLed(PIN_PROXIMITY_RIGHT, PIN_LED_C);
  } else {
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);
  }
}

void mirrorProxLed(int sensorPin, int ledPin) {
  digitalWrite(ledPin, analogRead(sensorPin) < 200 ? HIGH : LOW);
}

