#include "TemperatureSensor.h"
#include <avr/io.h>
#include <util/delay.h>

void TemperatureSensor::init(void) {
  //analogReference( INTERNAL1V1 );

  // ATTiny85 datasheet p140 (17.13.2), p137 (17.12)
  // Configure ADMUX
  ADMUX = 0x0F;                        // Selects temperature sensor
  ADMUX &= ~(1 << ADLAR);               // Right-adjust result
  ADMUX |= (1 << REFS1);                // Sets the Reference Voltage to 1.1V
  ADMUX &= ~((1 << REFS0) | (1 << REFS2)); // Assures that the Reference Voltage is 1.1V
  _delay_ms(2);

  // Configure ADCSRA
  ADCSRA &= ~((1 << ADATE) | (1 << ADIE)); // Disables Autotrigger and Interrupt
  ADCSRA |= (1 << ADEN);                // Enables the ADC
  ADCSRA |= (1 << ADSC);                // Starts the first conversion (need to set at each conversion)

  // Seed samples
  double raw_temp;
  while ((raw_temp = getTemperature_Raw()) < 0);
  for (int i = 0; i < TEMPERATURE_SAMPLES; i++) {
    temperatureReadings[i] = raw_temp;
  }
}

int TemperatureSensor::getTemperature_Raw() {
  if (ADCSRA & (1 << ADSC)) {           // Tests if there is a conversion running
    return -1;
  } else {
    int ret = ADCL | (ADCH << 8);       // Get the previous conversion result
    ADCSRA |= (1 << ADSC);              // Starts a new AD conversion
    return ret;
  }
}

double TemperatureSensor::getTemperature_Lsb(void) {
  int duplicatedReadings[TEMPERATURE_SAMPLES];
  int raw_temp;

  // remember the sample
  if ((raw_temp = getTemperature_Raw()) > 0) {
    temperatureReadings[pos] = raw_temp;
    pos++;
    pos %= TEMPERATURE_SAMPLES;
  }

  // copy the samples
  for ( int i = 0; i < TEMPERATURE_SAMPLES; i++ ) {
    duplicatedReadings[i] = temperatureReadings[i];
  }

  // bubble extremes to the ends of the array
  int extremes_count = TEMPERATURE_SAMPLES / EXTREMES_RATIO;
  //int swap;   // In case you want it old way
  for (int i = 0; i < extremes_count; ++i) { // percent of iterations of bubble sort on small N works faster than Q-sort
    for (int j = 0; j < (TEMPERATURE_SAMPLES - 1); j++) {
      if (duplicatedReadings[i] > duplicatedReadings[i + 1]) {
        // XOR Swap Algorithm
        duplicatedReadings[i] ^= duplicatedReadings[i + 1]; // X := X XOR Y
        duplicatedReadings[i + 1] ^= duplicatedReadings[i]; // Y := X XOR Y
        duplicatedReadings[i] ^= duplicatedReadings[i + 1]; // X := X XOR Y

        // Could be done using the old method: making use of a swap variable
        /*
        swap = duplicatedReadings[i];
        duplicatedReadings[i] = duplicatedReadings[i+1];
        duplicatedReadings[i+1] = swap;
        */
      }
    }
  }

  // average the middle of the array
  double sum_temp = 0;

  for ( int i = extremes_count; i < TEMPERATURE_SAMPLES - extremes_count; i++ ) {
    sum_temp += duplicatedReadings[i];
  }
  return sum_temp / ( TEMPERATURE_SAMPLES - extremes_count * 2 );
}


double TemperatureSensor::getTemperature_Celsius(void) {
  return getTemperature_Lsb() + OFFSET - 273;
}
