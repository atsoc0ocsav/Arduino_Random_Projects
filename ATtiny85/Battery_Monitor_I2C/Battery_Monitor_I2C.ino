/*
 * Coded by Vasco Costa for HANCAD/ CORATAM IT Project
 * 24/06/2014
 */

// Includes ////////////////////////////////////////////////////
#include "TemperatureSensor.h"
#include "CellVoltageSensor.h"
#include <TinyWireS.h>                  // wrapper class for I2C slave routines
#include <avr/io.h>
#include <util/delay.h>


// Definition //////////////////////////////////////////////////
#define I2C_SLAVE_ADDR  0x20             // i2c slave address
#define LED_PIN         1                // ATtiny Pin 6

// Variables ///////////////////////////////////////////////////
TemperatureSensor tempSensor;
CellVoltageSensor cellVoltageSensor;
uint16_t readedValues[3] = {-1,-1,-1};
uint16_t temperature = -1;
boolean readingEnable = true;

// I2C Request and Receive Methods ////////////////////////////////////////////////
void onRequest(){
  byte byteRcvd = 0;
  if (TinyWireS.available()) {          // got I2C input!
    //blinkLed(LED_PIN, 1);
    byteRcvd = TinyWireS.receive();     // get the byte from master

    switch (byteRcvd) {
      // Get Cell Count
      case 0x00: {
          TinyWireS.send(cellVoltageSensor.getCellCount());
          break;
        }

      // Get Cell Voltages
      case 0x01: {
          TinyWireS.send((readedValues[0] >> 8) && 0xFF);
          break;
        }

      case 0x02: {
          TinyWireS.send(readedValues[0] && 0xFF);
          break;
        }

      case 0x03: {
          TinyWireS.send((readedValues[1] >> 8) && 0xFF);
          break;
        }

      case 0x04: {
          TinyWireS.send(readedValues[1] && 0xFF);
          break;
        }

      case 0x05: {
          TinyWireS.send((readedValues[2] >> 8) && 0xFF);
          break;
        }

      case 0x06: {
          TinyWireS.send(readedValues[2] && 0xFF);
          break;
        }

      // Get Temperature
      case 0x30: {
        TinyWireS.send((temperature >> 8) && 0xFF);
        break;
      }

      case 0x31: {
        TinyWireS.send(temperature && 0xFF);
        break;
      }

      // Get Enable Status
      case 0x3F: {
        if(readingEnable){
          TinyWireS.send(0xAA);
        }else{
          TinyWireS.send(0xCC);
        }
      }

      default:
        //TinyWireS.send(0xFF);
        break;
    }
  }
}

void onReceive(){

}

// Default Methods ////////////////////////////////////////////////
void setup() {
  pinMode(LED_PIN, OUTPUT);             // for verification
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
}

void loop() {
  byte byteRcvd = 0;

  }
}

double getTemperature() {
  if(currentPin!=4){
    tempSensor.init();
    currentPin = 4;
  }

  return tempSensor.getTemperature_Celsius();
}
