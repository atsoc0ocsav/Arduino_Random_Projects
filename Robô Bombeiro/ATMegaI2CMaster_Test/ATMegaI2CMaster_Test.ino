#include <Wire.h>

int redLed=2;
int greenLed=3;
int pot=A8;

void setup() {
  Wire.begin();
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  digitalWrite(redLed,HIGH);
  digitalWrite(greenLed,HIGH);
  delay(2000);
  digitalWrite(redLed,LOW);
  digitalWrite(greenLed,HIGH);
}

void loop() {
  int val=map(analogRead(pot),0,1024,0,255);
  analogWrite(redLed,255-val);
  analogWrite(greenLed,val);

  //I2C Communication
  Wire.beginTransmission(4);
  Wire.write("val=");
  Wire.write(val);
  Wire.endTransmission();
  delay(500);
}





