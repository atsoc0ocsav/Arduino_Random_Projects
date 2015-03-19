
#include <Wire.h>
#include <SoftwareSerial.h>

#define ADDRESS 0x68 // Address of TPA81
#define SOFTREG 0x00 // Byte for software version
#define AMBIANT 0x01 // Byte for ambiant temperature

int temperature[] = {
  0,0,0,0,0,0,0,0}; // Array to hold temperature data

void setup(){
  Serial.begin(9600); // Starts software serial port for LCD03
  Wire.begin();
  delay(100); // Wait to make sure everything is powerd up
  Serial.println("Boot!");
  byte software = getData(SOFTREG); // Get software version 
}

void loop(){
  for(int i = 0; i < 8; i++){ // Loops and stores temperature data in array
    temperature[i] = getData(i+2);
  }

  char str[8];// = char[8];
  for(int x = 0; x < 8; x++){ 
    str[x]=temperature[x]; 
    Serial.print(temperature[x],DEC);
    Serial.print(',');
  }
  Serial.print(getData(AMBIANT),DEC);
  Serial.println();
  delay(50);

  // Serial.println(str); 
  int ambiantTemp = getData(AMBIANT); // Get reading of ambiant temperature and print to LCD03 screen
  // Serial.println(ambiantTemp);
}

byte getData(byte reg){ // Function to receive one byte of data from TPA81
  Wire.beginTransmission(ADDRESS); // Begin communication with TPA81
  Wire.write(reg); // Send reg to TPA81
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 1); // Request 1 byte
  while(Wire.available() < 1); // Wait for byte to arrive
  byte data = Wire.read(); // Get byte
  return(data); // return byte
}


