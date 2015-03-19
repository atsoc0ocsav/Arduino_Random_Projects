#include <Stepper.h>

const int stepsPerRevolution = 48;

//Stepper myStepper(stepsPerRevolution, 3,4,5,6);
Stepper myStepper(stepsPerRevolution,3,4); 

void setup() {
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  pinMode(11,OUTPUT);
}

void loop() {
  analogWrite(11,255);
  myStepper.setSpeed(400);
  myStepper.step(100);
  lock();
  delay(100);
  unlock();
  myStepper.step(-100);
  lock();
  delay(100);
  unlock();
}

void lock(){
  digitalWrite(10,LOW);
  analogWrite(11,0);
}

void unlock(){
  digitalWrite(10,HIGH);
  analogWrite(11,255);
}
