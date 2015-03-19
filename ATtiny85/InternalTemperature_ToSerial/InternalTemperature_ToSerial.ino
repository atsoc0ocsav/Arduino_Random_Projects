// Includes ////////////////////////////////////////////////////
#include <SoftwareSerial.h>


// Definition //////////////////////////////////////////////////
// General
#define rxPin 0
#define txPin 1
#define LED_PIN 4

// Temperature Readings
#define TEMPERATURE_SAMPLES 30
#define EXTREMES_RATIO 5
#define OFFSET 21


// Variables ///////////////////////////////////////////////////
int readings[TEMPERATURE_SAMPLES];
int pos;

SoftwareSerial mySerial(rxPin, txPin); // RX, TX


// Arduino Code ////////////////////////////////////////////////
void setup() {
  mySerial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  initTemperatureSensor();
}

void loop() {
  printTemperature();
  delay(100);
}


// Temperature Sensor Functions ////////////////////////////////
void initTemperatureSensor() {
  //analogReference( INTERNAL1V1 );

  // ATTiny85 datasheet p140 (17.13.2), p137 (17.12)
  // Configure ADMUX
  ADMUX = B1111;                        // Selects temperature sensor
  ADMUX &= ~(1 << ADLAR);               // Right-adjust result
  ADMUX |= (1 << REFS1);                // Sets the Reference Voltage to 1.1V
  ADMUX &= ~((1 << REFS0) | (1 << REFS2)); // Assures that the Reference Voltage is 1.1V

  // Configure ADCSRA
  ADCSRA &= ~((1 << ADATE) | (1 << ADIE)); // Disables Autotrigger and Interrupt
  ADCSRA |= (1 << ADEN);                // Enables the ADC
  ADCSRA |= (1 << ADSC);                // Starts the first conversion (need to set at each conversion)

  // Seed samples
  double raw_temp;
  while ((raw_temp = getTemperature_Raw()) < 0);
  for (int i = 0; i < TEMPERATURE_SAMPLES; i++) {
    readings[i] = raw_temp;
  }
}

int getTemperature_Raw() {
  if (ADCSRA & (1 << ADSC)) {           // Tests if there is a conversion running
    return -1;
  } else {
    int ret = ADCL | (ADCH << 8);       // Get the previous conversion result
    ADCSRA |= (1 << ADSC);              // Starts a new AD conversion
    return ret;
  }
}

double getTemperature_Lsb() {
  int duplicatedReadings[TEMPERATURE_SAMPLES];
  int raw_temp;

  // remember the sample
  if ((raw_temp = getTemperature_Raw()) > 0) {
    readings[pos] = raw_temp;
    pos++;
    pos %= TEMPERATURE_SAMPLES;
  }

  // copy the samples
  for ( int i = 0; i < TEMPERATURE_SAMPLES; i++ ) {
    duplicatedReadings[i] = readings[i];
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


double getTemperature_Celsius() {
  return getTemperature_Lsb() + OFFSET - 273;
}


void printTemperature() {
  mySerial.print("> R:");
  mySerial.print(getTemperature_Raw(), 0);
  mySerial.print(" L:");
  mySerial.print(getTemperature_Lsb(), 3);
  mySerial.print(" C:");
  mySerial.print(getTemperature_Celsius(), 3);
  mySerial.println(" # ");
}
