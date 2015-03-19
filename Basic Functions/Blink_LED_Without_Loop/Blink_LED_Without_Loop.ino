const int PINOUTPUT= 13;

int LEDState=LOW;
long interval=1000;
int lastMillis=0;

void setup(){
  pinMode(PINOUTPUT,OUTPUT);
}

void loop(){
  long currentMillis=millis();
  if(currentMillis-lastMillis>interval){
    lastMillis=currentMillis;
    if(LEDState==LOW){
      digitalWrite(PINOUTPUT,HIGH);
      LEDState=HIGH;
    }
    else{
      digitalWrite(PINOUTPUT,LOW);
      LEDState=LOW;
    }
  }
}
    
