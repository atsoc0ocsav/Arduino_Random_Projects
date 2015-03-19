#include <Servo.h>

Servo servo;

const int servoOutPin = 6;
const int buttonPin = 2;
const int ledPin = 3;

int stopValue = 90;

// Variables will change:
int mode = HIGH;             // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

int enableTime = 0;
int velocity = stopValue;
int maxRandSpeed = 50;
int runningDirection = LOW;
int previousRunningDirection = LOW;

long lastDebounceTime = 0;    // the last time the output pin was toggled
long debounceDelay = 50;      // the debounce time; increase if the output flickers
long enableTime = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(servoOutPin);
  randomSeed(analogRead(0));
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(ledPin, LOW);
}

void loop() {
  readInput();
  outputToMotors(); 
}

void readInput(){
   int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        mode = !mode;
      }
    }
  }
  
  lastButtonState = reading;
  digitalWrite(ledPin, mode);
}

void outputToMotors(){
  if(mode){
    int analogValue = analogRead(A1);
    int angleValue = map(analogValue, 0, 1023, 1, 179);
    servo.write(angleValue);
  }else{
    if(enableTime <= 0){
      enableTime = random(10000);
      velocity = random(maxRandSpeed);
      
      if(random(1)>=0.5){
        runningDirection = LOW;
      } else {
        runningDirection = HIGH;
      }
    }
    
    if(runningDirection != previousRunningDirection){
      servo.write(stopValue);
      previousRunningDirection = runningDirection;
    }
    
    if(runningDirection){
      servo.write(stopValue+velocity);
    } else {
      servo.write(stopValue-velocity);
    }
    
    enableTime--;
  }
}
