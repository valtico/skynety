#define PIN_LED 13

#define PIN_PROXIMITY_LEFT A8
#define PIN_PROXIMITY_BOTTOM A6
#define PIN_PROXIMITY_RIGHT A4

void setup() {
  Serial.begin(9600);
  while (!Serial) ;

  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_PROXIMITY_LEFT, INPUT);
  pinMode(PIN_PROXIMITY_BOTTOM, INPUT);
  pinMode(PIN_PROXIMITY_RIGHT, INPUT);
}

void loop() {
  int valProxLeft = analogRead(PIN_PROXIMITY_LEFT);
  int valProxBot = analogRead(PIN_PROXIMITY_BOTTOM);
  int valProxRight = analogRead(PIN_PROXIMITY_RIGHT);

  Serial.print(" left=");
  Serial.print(valProxLeft);
  Serial.println();

  Serial.print(" bot=");
  Serial.print(valProxBot);
  Serial.println();

  Serial.print(" right=");
  Serial.print(valProxRight);
  Serial.println();

  delay(1000);
}

