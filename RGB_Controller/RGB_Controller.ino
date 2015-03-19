// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11
#include <math.h>
 
#define FADESPEED 8     // make this higher to slow down
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}
 
 
void loop() {
  int r, g, b;
  int value=0;
  // fade from blue to violet
  for (r = 0; r < 256; r++) {
    value=int(fscale(0,255,0,255,r,0));
    analogWrite(REDPIN, value);
    delay(FADESPEED);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) {
    value=int(fscale(0,255,0,255,b,0));
    analogWrite(BLUEPIN, value);
    delay(FADESPEED);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) {
    value=int(fscale(0,255,0,255,g,0)); 
    analogWrite(GREENPIN, value);
    delay(FADESPEED);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) {
    value=int(fscale(0,255,0,255,r,0)); 
    analogWrite(REDPIN, value);
    delay(FADESPEED);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) {
    value=int(fscale(0,255,0,255,b,0)); 
    analogWrite(BLUEPIN, value);
    delay(FADESPEED);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) {
    value=int(fscale(0,255,0,255,g,0)); 
    analogWrite(GREENPIN, value);
    delay(FADESPEED);
  } 
}


float fscale( float originalMin, float originalMax, float newBegin, float newEnd, float inputValue, float curve){
  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;
 
  // condition curve parameter
  // limit range
  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;
  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output 
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function
  
  // Check for out of range inputValues
  if (inputValue < originalMin) inputValue = originalMin;
  if (inputValue > originalMax) inputValue = originalMax;
   
  // Zero Refference the values
  OriginalRange = originalMax - originalMin;
  if (newEnd > newBegin) NewRange = newEnd - newBegin;
  else{
     NewRange = newBegin - newEnd; 
    invFlag = 1;
  }
  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float
  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine 
  if (originalMin > originalMax ) return 0;
  if (invFlag == 0) rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;
  else  // invert the ranges
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange); 
  return rangedValue;
}

