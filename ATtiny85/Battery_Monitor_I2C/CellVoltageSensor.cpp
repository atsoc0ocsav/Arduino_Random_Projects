#include "TemperatureSensor.h"
#include <avr/io.h>
#include <util/delay.h>

// Analog Read Functions ////////////////////////////////
double CellVoltageSensor::getCellVoltage(int cell) {
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

double CellVoltageSensor::getInputVoltage(int portNumber) {
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

uint16_t CellVoltageSensor::readAnalogInput(int portNumber) {
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