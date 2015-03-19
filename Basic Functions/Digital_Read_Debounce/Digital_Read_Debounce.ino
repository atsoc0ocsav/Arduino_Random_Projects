const int LedOUTPUT=13;
const int PortInput=2;
int LedState=LOW;
int lastState=0;

void setup(){
  Serial.begin(2400);
  pinMode(2,INPUT);
  pinMode(LedOUTPUT,OUTPUT);
}

void loop(){
  int currentState=digitalRead(PortInput);
  
  if(currentState==1 && lastState==0){
    Serial.println(currentState, DEC);
    if(currentState==1 &&  LedState==LOW){
      digitalWrite(LedOUTPUT, HIGH);
      LedState=HIGH;
    }
    else{
      if(currentState==1 && LedState==HIGH){
        digitalWrite(LedOUTPUT,LOW);
        LedState=LOW;
      }
    }
    delayMicroseconds(300);
    lastState=1;
  }
  else{
    if(currentState==0 && lastState==1)
      lastState=0;
  }
}
