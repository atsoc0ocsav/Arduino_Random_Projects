
#include <Wire.h>
#include <SoftwareSerial.h>

// I2C Variables
#define ADDRESSA 0x68 // Address of TPA81
#define ADDRESSB 0x69 // Address of TPA81
#define SOFTREG 0x00 // Byte for software version
#define AMBIANT 0x01 // Byte for ambiant temperature

// Temperature Reading
int temperatureA[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0
}; // Array to hold sensor A temperature data
int temperatureB[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0
}; // Array to hold sensor B temperature data


void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  Wire.begin();
  delay(100); // Wait to make sure everything is powered up
}

void loop() {
  readTemperatures();

  for (int i = 0; i < 9; i++) { //Ambient Temperature on 9th position (when index=8)
    byte b = temperatureA[i];
    Serial.write(b);
  }
  Serial.flush();
  delay(50);
}

void readTemperatures() {
  for (int i = 0; i < 8; i++) { // Loops and stores temperature data in array
    temperatureA[i] = getTempData(i + 2, 1);
    //temperatureB[i] = getTempData(i + 2, 2);
  }

  temperatureA[8] = getTempData(AMBIANT, 1);
  //temperatureB[8] = getTempData(AMBIANT, 2);
}

byte getTempData(byte reg, int id) { // Function to receive one byte of data from TPA81
  int ADDRESS;
  switch (id) {
    case 1:
      ADDRESS = ADDRESSA;
      break;
    case 2:
      ADDRESS = ADDRESSB;
      break;
  }

  Wire.beginTransmission(ADDRESS); // Begin communication with TPA81
  Wire.write(reg); // Send reg to TPA81
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 1); // Request 1 byte
  while (Wire.available() < 1); // Wait for byte to arrive
  byte data = Wire.read(); // Get byte
  return (data); // return byte
}
