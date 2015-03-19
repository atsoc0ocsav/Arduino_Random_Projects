#include <Servo.h>

Servo servo;

const int ServoOut = 6;
int value = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(ServoOut);
}

void loop() {
  while (Serial.available() > 0) {
    value = Serial.parseInt();

    if (Serial.read() == '\n') {
      //int analogValue = analogRead(A0);
      //int angleValue = map(analogValue,0,1023,0,179);
      Serial.println(value);

      value = constrain(value, 0, 179);
      servo.write(value);
    }
  }
}

