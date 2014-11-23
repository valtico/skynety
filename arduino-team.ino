#define PIN_LED 13

#define PIN_PROXIMITY_LEFT A8
#define PIN_PROXIMITY_BOTTOM A6
#define PIN_PROXIMITY_RIGHT A4

void setup() {
  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_PROXIMITY_LEFT, INPUT);
  pinMode(PIN_PROXIMITY_BOTTOM, INPUT);
  pinMode(PIN_PROXIMITY_RIGHT, INPUT);
}

void loop() {
}

