#include <Wire.h>

#define ADDRESSA 0x68 // Address of TPA81
#define ADDRESSB 0x69 // Address of TPA81
#define ADDRESSC 0x6A // Address of TPA81
#define SOFTREG 0x00 // Byte for software version
#define AMBIANT 0x01 // Byte for ambiant temperature

int ledCandlePin=3;
int relayFanPin=2;
int startButtonPin=8;
int stopButtonPin=9;
int bumperLeftPin=4;
int bumperRightPin=5;

int temperatureA[] = {
  0,0,0,0,0,0,0,0,0}; // Array to hold sensor A temperature data
int temperatureB[] = {
  0,0,0,0,0,0,0,0,0}; // Array to hold sensor B temperature data
int temperatureC[] = {
  0,0,0,0,0,0,0,0,0}; // Array to hold sensor C temperature data

boolean startPressed=false;
boolean stopPressed=false;
boolean bumperLeftPressed=false;
boolean bumperRightPressed=false;

void setup() {
  // Set I/O Ports
  pinMode(ledCandlePin,OUTPUT);
  pinMode(relayFanPin,OUTPUT);
  pinMode(startButtonPin,INPUT_PULLUP);
  pinMode(stopButtonPin,INPUT_PULLUP);
  pinMode(bumperLeftPin,INPUT_PULLUP);
  pinMode(bumperRightPin,INPUT_PULLUP);

  // Test Functions
  digitalWrite(ledCandlePin,HIGH);
  digitalWrite(relayFanPin,HIGH);
  delay(500);
  digitalWrite(ledCandlePin,LOW);
  digitalWrite(relayFanPin,LOW);

  // Begin Communication Protocols
  Serial.begin(57600);
  Wire.begin();
  delay(25); // Wait to make sure everything is powerd up
}

int currentTime;
void loop() {
  while(!Serial.available()){
    boolean pressed=false;
    if(!digitalRead(startButtonPin)){
      startPressed=true;
      pressed=true;
    }
    if(!digitalRead(stopButtonPin)){
      stopPressed=true;
      pressed=true;
    }
    if(!digitalRead(bumperLeftPin)){
      bumperLeftPressed=true;
      pressed=true;
    }
    if(!digitalRead(bumperRightPin)){
      bumperRightPressed=true;
      pressed=true;
    }
    if(pressed){
      delay(100);
      pressed=false;
    }
    readTemperatures();
    delay(50);    
  }
  makeSerialCommunications();
}

void makeSerialCommunications(){
  char operation=Serial.read();
  switch(operation){
    // Read Buttons Values
  case 's':
    char str[5];
    if(startPressed)
      str[0]='1';
    else
      str[0]='0';
    if(stopPressed)
      str[1]='1';
    else
      str[1]='0';
    if(bumperLeftPressed)
      str[2]='1';
    else
      str[2]='0';
    if(bumperRightPressed)
      str[3]='1';
    else
      str[3]='0';
    str[4]='\0';
    Serial.print(str);
    startPressed=false;
    stopPressed=false;
    bumperLeftPressed=false;
    bumperRightPressed=false;
    break;

    // Turn off candle Led
  case 'l':
    digitalWrite(ledCandlePin,LOW);
    break;

    // Turn on candle Led
  case 'L':
    digitalWrite(ledCandlePin,HIGH);
    break;

    // Flash Led Ten Times
  case 'f':
    {
      boolean previousState=digitalRead(ledCandlePin);
      for(int i=0;i<10;i++){
        digitalWrite(ledCandlePin,HIGH);
        delay(50);
        digitalWrite(ledCandlePin,LOW);
        delay(50);
      }
      digitalWrite(ledCandlePin,previousState);
    }
    break;

    //Enable Relay
  case 'R':
    digitalWrite(relayFanPin,HIGH);
    break;

    //Disable Relay
  case 'r':
    digitalWrite(relayFanPin,LOW);
    break;

    // Read Sensor 1
  case 'a':
    for(int x = 0; x < 9; x++){
      byte b=temperatureA[x]; 
      Serial.write(b);
    }
    Serial.flush();
    break;

    // Read Sensor 2
  case 'b':
    for(int x = 0; x < 9; x++){
      byte b=temperatureB[x]; 
      Serial.write(b);
    }
    Serial.flush();
    break;

    // Read Sensor 3
  case 'c':
    for(int x = 0; x < 9; x++){
      byte b=temperatureC[x]; 
      Serial.write(b);
    }
    Serial.flush();
    break;
  }
}

byte getTempData(byte reg,int id){ // Function to receive one byte of data from TPA81
  int ADDRESS;
  switch(id){
  case 1:
    ADDRESS=ADDRESSA;
    break;
  case 2:
    ADDRESS=ADDRESSB;
    break;
  case 3:
    ADDRESS=ADDRESSC;
    break;
  }
  Wire.beginTransmission(ADDRESS); // Begin communication with TPA81
  Wire.write(reg); // Send reg to TPA81
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 1); // Request 1 byte
  while(Wire.available() < 1); // Wait for byte to arrive
  byte data = Wire.read(); // Get byte
  return(data); // return byte
}

void readTemperatures(){
  for(int i = 0; i < 8; i++){ // Loops and stores temperature data in array
    temperatureA[i] = getTempData(i+2,1);
    temperatureB[i] = getTempData(i+2,2);
    temperatureC[i] = getTempData(i+2,3);
  }

  temperatureA[8] = getTempData(AMBIANT,1);
  temperatureB[8] = getTempData(AMBIANT,2);
  temperatureC[8] = getTempData(AMBIANT,3);
}















