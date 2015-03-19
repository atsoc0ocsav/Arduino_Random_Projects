int incomingByte = 0;   // for incoming serial data

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial1.print(incomingByte);
  }
}
