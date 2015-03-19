#include <Wire.h>

#define ADDRESSA 0x68 // Address of TPA81
#define ADDRESSB 0x68 // Address of TPA81
#define SOFTREG 0x00 // Byte for software version
#define AMBIANT 0x01 // Byte for ambiant temperature

int ledCandlePin=3;
int relayFanPin=4;
int startButtonPin=5;
int stopButtonPin=6;
int bumperLeftPin=7;
int bumperRightPin=8;

int ambientTemperature=0;

byte temperatureA[] = {
  0,0,0,0,0,0,0,0,0}; // Array to hold sensor A temperature data
byte temperatureB[] = {
  0,0,0,0,0,0,0,0,0}; // Array to hold sensor B temperature data

boolean startPressed=false;
boolean stopPressed=false;
boolean bumperLeftPressed=false;
boolean bumperRightPressed=false;

void setup() {
  // Set I/O Ports
  pinMode(ledCandlePin,OUTPUT);
  pinMode(relayFanPin,OUTPUT);
  pinMode(startButtonPin,INPUT);
  pinMode(stopButtonPin,INPUT);
  pinMode(bumperLeftPin,INPUT);
  pinMode(bumperRightPin,INPUT);

  // Test Functions
  digitalWrite(ledCandlePin,HIGH);
  digitalWrite(relayFanPin,HIGH);
  delay(250);
  digitalWrite(ledCandlePin,LOW);
  digitalWrite(relayFanPin,LOW);

  // Begin Communication Protocols
  Serial.begin(57600);
  Wire.begin();
  delay(25); // Wait to make sure everything is powerd up
}

void loop() {
  while(!Serial.available()){
    boolean pressed=false;
    if(digitalRead(startButtonPin)){
      startPressed=true;
      pressed=true;
    }
    if(digitalRead(stopButtonPin)){
      stopPressed=true;
      pressed=true;
    }
    if(digitalRead(bumperLeftPin)){
      bumperLeftPressed=true;
      pressed=true;
    }
    if(digitalRead(bumperRightPin)){
      bumperRightPressed=true;
      pressed=true;
    }
    if(pressed){
      delay(100);
      pressed=false;
    }
    //readTemperatures();
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
    //Serial.flush();
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
    Serial.write(temperatureA,9);
    break;

    // Read Sensor 2
  case 'b':
    Serial.write(temperatureB,9);
    break;
  }
}

byte getTempData(byte reg,int id){ // Function to receive one byte of data from TPA81
  int ADDRESS;
  if(id==0)
    ADDRESS=ADDRESSA; // Begin communication with TPA81
  else
    ADDRESS=ADDRESSB;
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
  }

  temperatureA[8] = getTempData(AMBIANT,1); // Get reading of ambiant temperature and print to LCD03 screen
  temperatureB[8] = getTempData(AMBIANT,2); // Get reading of ambiant temperature and print to LCD03 screen
}








