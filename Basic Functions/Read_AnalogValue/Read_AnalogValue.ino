const int PWMOut = 3;
int brightness = 0;


void setup() {
  Serial.begin(9600);
  pinMode(PWMOut, brightness);
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  brightness=map(sensorValue,0,1023,0,255);
  analogWrite(PWMOut, brightness);
}

