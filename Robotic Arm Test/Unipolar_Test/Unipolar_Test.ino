#include <Stepper.h>

//#define STEPS 48 //7,5º/Step
#define STEPS 200 //1,8º/Step

Stepper stepper=Stepper(STEPS,4,5,6,7);

void setup(){

}

void loop(){
  /*int speede = map(analogRead(A0),0,1024,0,400);
  int steps = map(analogRead(A1),0,1024,-200,200);
  digitalWrite(13,LOW);
  stepper.setSpeed(speede);
  stepper.step(steps);
  Serial.print("Speed: ");
  Serial.println(speede);
  Serial.print("Steps: ");
  Serial.println(steps);
  Serial.println("-----------------------");
  digitalWrite(13,HIGH);
  //delay(500);*/
  
  stepper.setSpeed(100);
  stepper.step(48);
  delay(500);
}
