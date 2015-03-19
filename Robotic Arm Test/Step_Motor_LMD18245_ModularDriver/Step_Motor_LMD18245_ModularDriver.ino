int enablePinA=13;
int stepPinA=11;
int directionPinA=12;

int enablePinB=10;
int stepPinB=8;
int directionPinB=9;

int enablePinC=7;
int stepPinC=5;
int directionPinC=6;

int sleep=12;
void setup() {
  pinMode(enablePinA,OUTPUT);
  pinMode(stepPinA,OUTPUT);
  pinMode(directionPinA,OUTPUT);

  pinMode(enablePinB,OUTPUT);
  pinMode(stepPinB,OUTPUT);
  pinMode(directionPinB,OUTPUT);

  pinMode(enablePinC,OUTPUT);
  pinMode(stepPinC,OUTPUT);
  pinMode(directionPinC,OUTPUT);

  digitalWrite(enablePinA,LOW);
  digitalWrite(directionPinA,LOW);
  
  digitalWrite(enablePinB,LOW);
  digitalWrite(directionPinB,HIGH);
  
  digitalWrite(enablePinC,LOW);
  digitalWrite(directionPinC,LOW);
}

void loop() {
  digitalWrite(stepPinA,HIGH);
  digitalWrite(stepPinB,HIGH);
  digitalWrite(stepPinC,HIGH);
  delayMicroseconds(sleep);
  //delay(sleep);
  digitalWrite(stepPinA,LOW);
  digitalWrite(stepPinB,LOW);
  digitalWrite(stepPinC,LOW);
  delayMicroseconds(sleep);
  //delay(sleep);

}


