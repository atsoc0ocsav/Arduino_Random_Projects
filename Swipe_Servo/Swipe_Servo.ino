#include <Servo.h>

Servo servo;

const int ServoOut = 5;
const int Delay = 10;
int steps = 1;
int ctr = 50;
boolean runMotor = false;

void setup() {
  Serial.begin(9600);
  servo.attach(ServoOut);

  Serial.print("Starting.... ");
  servo.write(0);
  delay(5000);
  Serial.println("now");
}

void loop() {
  if (Serial.available() > 0) {
    int ch = Serial.read();
    if ( ch == 'S')
      runMotor = true;
    if (ch == 's')
      runMotor = false;
    if (ch == 'r')
      ctr = 50;
  }
  if (runMotor) {
    servo.write(ctr);
    Serial.println(ctr);

    ctr += steps;
    if (ctr == 50 || ctr == 175)
      steps = -steps;

    delay(Delay);
  }
}
