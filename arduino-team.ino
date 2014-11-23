#define PIN_LED 13

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  blinkPin(PIN_LED);
}

void blinkPin(int pin) {
  blinkPin(pin, 1000);
}

void blinkPin(int pin, int delayMillis) {
  digitalWrite(pin, HIGH);
  delay(delayMillis / 2);
  digitalWrite(pin, LOW);
  delay(delayMillis / 2);
}

