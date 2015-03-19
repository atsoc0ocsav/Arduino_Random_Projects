#include <Wire.h>

int x = 1;
boolean todo = false;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  Serial.println("Started!");
}

void loop() {
  if (Serial.available() > 0) {
    switch (Serial.read()) {
      case 'a':
        x = 0x00;
        todo = true;
        break;

      case 'b':
        x = 0x10;
        todo = true;
        break;

      case 'c':
        x = 0x20;
        todo = true;
        break;

      case 'd':
        x = 0x30;
        todo = true;
        break;

      default:
        Serial.println("Chacacter not recognised!");
        todo = false;
        break;
    }

    if (todo) {
      Serial.print("Sending... ");
      Wire.beginTransmission(0x20);  // transmit to device #4
      Wire.write(x);                 // sends one byte
      Wire.endTransmission();        // stop transmitting

      Serial.print(x);
      Serial.println(" sent!");

      delay(2000);

      Wire.requestFrom(0x20, 2);    // request 2 bytes from slave device #2
      uint16_t value = 0;
      if (Wire.available()) {       // slave may send less than requested
        value |= Wire.read();
        value |= Wire.read() << 8;   // receive a byte as character
      }

      //value=10000;

      Serial.print("Readed: ");
      Serial.print(value);
      Serial.println();
      //delay(20);
    }

    while (Serial.available() > 0) {
      Serial.read();
    }
  }
  //delay(10);
}
