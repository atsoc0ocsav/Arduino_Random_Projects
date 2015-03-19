int led=13;
boolean lastState=HIGH;
int value;
int currentMillis=0;
int lastMillis=0;
int count=0;
int values[10]={
};
int arrayCurrentPos=0;


void setup(){
  pinMode(12,OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite(12,HIGH);
  Serial.begin(9600);
  analogReference(DEFAULT);
}

void loop(){
  currentMillis=millis();
  value=analogRead(1);
  //  Serial.println(value);
  verifyState();
  if(currentMillis-lastMillis>=10){
    count=count*100;
    values[arrayCurrentPos]=count;
    lastMillis=millis();
    arrayCurrentPos++;
    count=0;
  }
  if(arrayCurrentPos==10){
    int sum=0;
    for(int i=0;i<10;i++){
      sum+=values[i];
    }
    sum=sum/10;
    Serial.print("Average RPM");
    Serial.println(sum);
    arrayCurrentPos=0;
  }
}



void verifyState(){
  if(value<=5 && lastState==HIGH){
    lastState=LOW;
    count++;
  }
  else
    lastState=HIGH;
}



