#include <Stepper.h>

#define STEPS 200
Stepper stepper(24, 8, 9, 10, 11);
int velocity=2500;

int led=13;
int powersave=12;

void setup()
{
  stepper.setSpeed(4000);
  pinMode(led,OUTPUT);
  pinMode(powersave,OUTPUT);
  digitalWrite(powersave,HIGH);
}

void loop()
{
  velocity=map(analogRead(0),0,1024,STEPS,3000);
  stepper.setSpeed(velocity);
  digitalWrite(13,HIGH);
  digitalWrite(powersave,LOW);
  stepper.step(STEPS);
  digitalWrite(powersave,HIGH);
  digitalWrite(13,LOW);
}


