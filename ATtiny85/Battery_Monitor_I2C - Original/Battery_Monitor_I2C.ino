/*
 * Coded by Vasco Costa for HANCAD/ CORATAM IT Project
 * 24/06/2014
 */

// Includes ////////////////////////////////////////////////////
#include "TemperatureSensor.h"
#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#include <avr/io.h>
#include <util/delay.h>


// Definition //////////////////////////////////////////////////
// Analog Pin for Each Cell
#define PIN_126V        0                // Cell 3
#define PIN_84V         3                // Cell 2
#define PIN_42V         2                // Cell 1

// Input correspondent to the desired voltage (TO-DO: get this better....)
#define TARGET_126V     920              // 12.6V
#define TARGET_84V      614              // 8,4V
#define TARGET_42V      305              // 4,2V

// I2C
#define I2C_SLAVE_ADDR  0x20             // i2c slave address
#define LED_PIN         1                // ATtiny Pin 6


// Variables ///////////////////////////////////////////////////
int currentPin = -1;
TemperatureSensor tempSensor;


// Arduino Code ////////////////////////////////////////////////
void setup() {
  pinMode(LED_PIN, OUTPUT);             // for verification
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
}

void loop() {
  byte byteRcvd = 0;
  if (TinyWireS.available()) {          // got I2C input!
    //blinkLed(LED_PIN, 1);
    byteRcvd = TinyWireS.receive();     // get the byte from master

    switch (byteRcvd) {
      case 0x00:
        {
          uint16_t voltage = (uint16_t)(getCellVoltage(1) * 1000);
          blinkLed(LED_PIN, 1);
          TinyWireS.send(voltage);
          TinyWireS.send(voltage >> 8);
          break;
        }

      case 0x10: {
          uint16_t voltage = (uint16_t)(getCellVoltage(2) * 1000);
          blinkLed(LED_PIN, 2);
          TinyWireS.send(voltage);
          TinyWireS.send(voltage >> 8);
          break;
        }

      case 0x20:
        {
          uint16_t voltage = (uint16_t)(getCellVoltage(3) * 1000);
          blinkLed(LED_PIN, 3);
          TinyWireS.send(voltage);
          TinyWireS.send(voltage >> 8);
          break;
        }

      case 0x30:
        {
          uint16_t temperature = (uint16_t)(getTemperature() * 100);
          blinkLed(LED_PIN, 4);
          TinyWireS.send(temperature);
          TinyWireS.send(temperature >> 8);
          break;
        }

      default:
        TinyWireS.send(0);
        break;
    }

    //blinkLed(LED_PIN, 1);
  }
}

void blinkLed(byte led, byte times) {
  for (byte i = 0; i < times; i++) {
    digitalWrite(led, HIGH);
    delay (50);
    digitalWrite(led, LOW);
    delay (50);
  }
}


// Analog Read Functions ////////////////////////////////
double getCellVoltage(int cell) {
  switch (cell) {
    case 1:
      return getInputVoltage(PIN_42V);
      break;
    case 2:
      return (getInputVoltage(PIN_84V) - getInputVoltage(PIN_42V));
      break;
    case 3:
      return (getInputVoltage(PIN_126V) - getInputVoltage(PIN_84V));
      break;
  }
}

double getInputVoltage(int portNumber) {
  double multiplier = 0;
  double voltage = 0;

  switch(portNumber){
    case PIN_126V:
      {
        voltage = 12.6;
        multiplier = TARGET_126V;
        break;
      }
    case PIN_84V:
      {
        voltage = 8.4;
        multiplier = TARGET_84V;
        break;
      }
    case PIN_42V:
      {
        voltage = 4.2;
        multiplier = TARGET_42V;
        break,
      }
    default:
      break;
  }

  return ((readAnalogInput(portNumber) * voltage) / multiplier);
}

int readAnalogInput(int portNumber) {
  if (portNumber != currentPin) {
    currentPin = portNumber;

    // ATTiny85 datasheet p134 to p138
    ADMUX = portNumber & 0xFF;                    // Selects the channel to read
    ADMUX &= ~(1 << ADLAR);                       // Right-adjust result
    ADMUX |= ((1 << REFS1) | (1 << REFS2));       // Sets the Reference Voltage to 2.56V
    ADMUX &= ~(1 << REFS0);                       // Assures that the Reference Voltage is 2.56V
    _delay_ms(2);

    // Configure ADCSRA
    ADCSRA &= ~((1 << ADATE) | (1 << ADIE));      // Disables Autotrigger and Interrupt
    ADCSRA |= (1 << ADEN);                        // Enables the ADC
    ADCSRA |= (1 << ADSC);                        // Starts the a conversion (need to set to start each conversion)
    _delay_ms(2);

    while (ADCSRA & (1 << ADSC));                 // Wait while the conversion is running
    ADCSRA |= (1 << ADSC);                        // Starts the a conversion (discard first values)
  }

  while (ADCSRA & (1 << ADSC));                   // Tests if there is a conversion running
  int ret = ADCL | (ADCH << 8);                   // Get the previous conversion result
  ADCSRA |= (1 << ADSC);                          // Starts a new conversion

  return ret;
}

double getTemperature() {
  if(currentPin!=4){
    tempSensor.init();
    currentPin = 4;
  }

  return tempSensor.getTemperature_Celsius();
}
