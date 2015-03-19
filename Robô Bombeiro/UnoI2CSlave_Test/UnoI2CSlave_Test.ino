#include <Wire.h>

int redLed=11;
int greenLed=10;
int blueLed=6;

void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveData);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(blueLed,OUTPUT);
  Serial.begin(9600);
  
  //Test Outputs
  digitalWrite(redLed,HIGH);
  digitalWrite(greenLed,HIGH);
  digitalWrite(blueLed,HIGH);
  delay(3000);
  digitalWrite(redLed,LOW);
  digitalWrite(blueLed,LOW);
}

int counter=0;
void loop() {
  delay(100);
  Serial.print(counter);
  Serial.println(" - No data!");
  counter++;
}

void receiveData(int howMany){
  String str="";
  int val=0;
  digitalWrite(blueLed,HIGH);
  while(Wire.available()>0){
    char c=Wire.read();
    Serial.print("Char: ");
    Serial.println(c); 
    //str+=c;
//    if(str.compareTo("val=")){
//      if(Wire.available()==3)
//        val+=Wire.read()*100;
//      else{
//        if(Wire.available()==2)
//          val+=Wire.read()*10;
//        else
//          val+=Wire.read();
//      }
//    }
  }
  analogWrite(redLed,255-val);
  analogWrite(greenLed,val);
  Serial.print("Received String: ");
  Serial.println(str);
  Serial.print("Value: ");
  Serial.println(val);
  digitalWrite(blueLed,LOW);
}





