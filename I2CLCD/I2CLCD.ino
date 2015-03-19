#include <I2C.h>

/* Uses http://dsscircuits.com/articles/arduino-i2c-master-library.html */

void setup() {
  Serial.begin (115200);
  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  I2c.pullup(true);
  I2c.scan();
}  // end of setup

void loop() {
}


