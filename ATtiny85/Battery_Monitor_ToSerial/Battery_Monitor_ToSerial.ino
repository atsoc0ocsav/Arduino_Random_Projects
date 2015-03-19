// Includes ////////////////////////////////////////////////////
#include <SoftwareSerial.h>
#include "TemperatureSensor.h"


// Definition //////////////////////////////////////////////////
// General
#define rxPin 0
#define txPin 1
#define LED_PIN 4

// Pin for Each Cell
#define PIN_126V 3           // Cell 3
#define PIN_84V  2           // Cell 2
#define PIN_42V  1           // Cell 1

// Input correspondent to the desired voltage
#define TARGET_126V 920      // 12.6V
#define TARGET_84V 614       // 8,4V
#define TARGET_42V 305       // 4,2V


// Variables ///////////////////////////////////////////////////
SoftwareSerial mySerial(rxPin, txPin); // RX, TX
TemperatureSensor tempSensor;
int currentPin = -1;

// Arduino Code ////////////////////////////////////////////////
void setup() {
  mySerial.begin(9600);
}

void loop() {
  mySerial.print("[1]: ");
  mySerial.print(getCellVoltage(PIN_42V), 3);
  mySerial.print("v [2]: ");
  mySerial.print(getCellVoltage(PIN_84V), 3);
  mySerial.print("v [3]: ");
  mySerial.print(getCellVoltage(PIN_126V), 3);
  mySerial.print("v [T]: ");
  mySerial.print(getTemperature());
  mySerial.println("ºC");
  delay(100);
}


// Analog Read Functions ////////////////////////////////
int readAnalogInput(int portNumber) {
  if (portNumber != currentPin) {
    currentPin = portNumber;

    // ATTiny85 datasheet p134 to p138
    ADMUX = portNumber & 0xFF;                      // Selects the channel to read
    ADMUX &= ~(1 << ADLAR);                         // Right-adjust result
    ADMUX |= ((1 << REFS1) | (1 << REFS2));       // Sets the Reference Voltage to 2.56V
    ADMUX &= ~(1 << REFS0);                       // Assures that the Reference Voltage is 2.56V
    delay(2);

    // Configure ADCSRA
    ADCSRA &= ~((1 << ADATE) | (1 << ADIE));      // Disables Autotrigger and Interrupt
    ADCSRA |= (1 << ADEN);                        // Enables the ADC
    ADCSRA |= (1 << ADSC);                        // Starts the a conversion (need to set to start each conversion)
    delay(10);
  }

  while (ADCSRA & (1 << ADSC));                   // Tests if there is a conversion running
  int ret = ADCL | (ADCH << 8);                   // Get the previous conversion result
  ADCSRA |= (1 << ADSC);                          // Starts a new conversion

  return ret;
}

double getInputVoltage(int portNumber) {
  double multiplier = 0;
  double voltage = 0;

  if (PIN_126V == portNumber) {
    voltage = 12.6;
    multiplier = TARGET_126V;
  } else {
    if (PIN_84V == portNumber) {
      voltage = 8.4;
      multiplier = TARGET_84V;
    } else {
      if (PIN_42V == portNumber) {
        voltage = 4.2;
        multiplier = TARGET_42V;
      } else {
        mySerial.println("[ERROR] Input Voltage");
      }
    }
  }
  return ((readAnalogInput(portNumber) * voltage) / multiplier);
}

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

double getTemperature(){
  tempSensor.init();
  currentPin=4;
  return tempSensor.getTemperature_Celsius();
}
