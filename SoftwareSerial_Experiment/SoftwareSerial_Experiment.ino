#include <SoftwareSerial.h>

#define rxPin 0
#define txPin 1
#define LED_PIN 4

SoftwareSerial mySerial(rxPin, txPin); // RX, TX

int i = 0;

void setup() {
  mySerial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  mySerial.print("Int i=");
  mySerial.print(i);
  mySerial.println();

  i++;
  if (i == 1000)
    i = 0;

  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
}
