#include <Wire.h>

int x = 1;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  Serial.println("Started!");
}

void loop() {
  if (Serial.available() > 0) {
    Serial.print("Sending... ");
    Wire.beginTransmission(0x26); // transmit to device #4
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting

    Serial.print(x);
    Serial.println(" sent!");
    x++;

    delay(500*x);

    Wire.requestFrom(0x26, 1);    // request 6 bytes from slave device #2
    while (Wire.available()) {  // slave may send less than requested
      int c = Wire.read(); // receive a byte as character
      Serial.print(c);         // print the character
    }

    Serial.println();
    delay(500);

    while (Serial.available() > 0) {
      Serial.read();
    }
  }
  delay(500);
}
