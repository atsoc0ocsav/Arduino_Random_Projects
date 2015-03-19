//Uno Esquerda
#include <Wire.h>

byte read_register = 0x00;
int ret = 0;
int readStuff = 0;

void setup()
{
  Wire.begin(0x0A);                // join i2c bus with address #2
  Wire.onRequest(requestEvent);  // Sending information back to the NXT!
  Wire.onReceive(receiveI2C);    // Receiving information!
  Serial.begin(9600);
  Serial.println("Starting");
}

void loop()
{
  delay(100);
}

// When data is received from NXT, this function is called.
void receiveI2C(int bytesIn)
{
  readStuff=0x00;
  Serial.print("bytesIn=");
  Serial.println(bytesIn);
  if(bytesIn > 1 ) {
    for(int i = 0 ; i < bytesIn && Wire.available() ; i++) {
      int data = Wire.read();
      readStuff = readStuff| (data << bytesIn-i-1);
    }
    Serial.print("Wire=");
    Serial.println(Wire.available());
    Serial.print("Received= ");
    Serial.println(readStuff);
  }
  else{
    //asking for data
    Wire.read();
  }
}

void requestEvent()
{
  Serial.println("Response needed!");
  Serial.println();
  byte arr[] = {
    readStuff     };
  Wire.write(arr,1);  
}


