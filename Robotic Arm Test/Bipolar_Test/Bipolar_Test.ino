#include <Stepper.h>

#define STEPS 200 //1,8º/Step

Stepper stepper=Stepper(STEPS,5,6);

void setup(){
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  //int speede = map(analogRead(A0),0,1024,0,400);
  //int steps = map(analogRead(A1),0,1024,-200,200);
  digitalWrite(13,HIGH);
  Serial.println("Em funcionamento");
  //stepper.setSpeed(speede);
  //stepper.step(steps);
  stepper.setSpeed(2);
  stepper.step(400);
  /*Serial.print("Speed: ");
  Serial.println(speede);
  Serial.print("Steps: ");
  Serial.println(steps);
  Serial.println("-----------------------");
  digitalWrite(13,HIGH);*/
  Serial.println("Stop");
  digitalWrite(13,LOW);
  delay(500);
  
}
