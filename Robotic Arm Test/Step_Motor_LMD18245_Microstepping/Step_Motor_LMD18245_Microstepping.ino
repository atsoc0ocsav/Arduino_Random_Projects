int speedy=600;
int outPin=8;

void setup() {
  pinMode(outPin,OUTPUT);
}

void loop() {
  for(int i=0;i<3200;i++){
    digitalWrite(outPin,HIGH);
    delayMicroseconds(speedy);
    digitalWrite(outPin,LOW);
    delayMicroseconds(speedy);
  }
  delay(3000);
}
