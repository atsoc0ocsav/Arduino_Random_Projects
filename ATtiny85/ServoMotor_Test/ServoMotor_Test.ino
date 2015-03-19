#include <SoftwareServo.h>

SoftwareServo myServo;
void setup() {
  myServo.attach(0);
  SoftwareServo::refresh();
}

void loop() {
  for (int i = 0; i <= 255; i++) {
    myServo.write(i);
    SoftwareServo::refresh();
    delay(2);
  }
  for (int i = 255; i >= 0; i--) {
    myServo.write(i);
    SoftwareServo::refresh();
    delay(2);
  }
  
}
