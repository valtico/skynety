#define PIN_LED 13
#define PIN_LED_A 15
#define PIN_LED_B 16
#define PIN_LED_C 17

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LED_A, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_C, OUTPUT);
}

void loop() {
  blinkPin(PIN_LED);
  blinkPin(PIN_LED_A);
  blinkPin(PIN_LED_B);
  blinkPin(PIN_LED_C);
}

void blinkPin(int pin) {
  blinkPin(pin, 500);
}

void blinkPin(int pin, int delayMillis) {
  digitalWrite(pin, HIGH);
  delay(delayMillis / 2);
  digitalWrite(pin, LOW);
  delay(delayMillis / 2);
}

