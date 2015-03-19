/**
* Author: Vasco Craveiro Costa
* Group: Eduardo Gonzalez, Daniel Sousa e Rui Madeira
* For: MCG ISCTE-IUL 2013-2014
*
* ----- Gear Clock Software -----
* Version: 1.2
*
* To be used on a Atmel ATiny85
* - Pins 0,1,2 and three to control gate of the darlingtons
*   (or transistors) to power up the motor.
* - Pin 4 reserved for the ajust motor (it disables the motor
*   so you can move the gears freely
*
* -- Version History --
* 1.2 - Button press processing improved - Vasco Craveiro Costa
* 1.1 - Deleted the delay when button is pressed (which was
*       deconfigure the TIMER1 - Vasco Craveiro Costa
* 1.0 - Original Version - Vasco Craveiro Costa
*
*/

#include <StepperImproved.h>
#define STEPS 48

StepperImproved stepper(STEPS, 0, 1, 2, 3);
int buttonPin = 4;
int time = 0;
boolean buttonPressed = false;
int CLOCK_CYCLE = 36; // Refresh each 9 seconds

// Set up of the port, motor and the timer (clock triggered) interrupt
void setup() {
  stepper.setSpeed(1);
  stepper.setMotorEnable();
  stepper.step(-1);

  pinMode(buttonPin, INPUT_PULLUP);
  delay(1000);

  cli();
  TCCR1 = 0;  // set all bits in TCCR1 register to 0

  // 121 count, match every 0.50 secs, 1MHz clock, prescaller @ 8192
  OCR1A = 121;

  TCCR1 |= (1 << CTC1); // clear timer on compare match

  // set CS11,CS12, and CS13 bits for 8192 prescaler
  //TCCR1 |= (0 << CS10);
  TCCR1 |= (1 << CS11);
  TCCR1 |= (1 << CS12);
  TCCR1 |= (1 << CS13);

  GTCCR |= (1 << PSR1); // reset Timer/Counter prescaler

  // Zero (Reset) Timer1 8-bit up counter value
  TCNT1 = 0;
  TIMSK |= (1 << OCIE1A); // enable Timer1 compare interrupt
  sei();
}

// Method called when an interrupt is triggered
ISR(TIMER1_COMPA_vect) {
  time++;
  if (time >= CLOCK_CYCLE) {
    time = 0;
    stepper.step(-1);
  }
}

// Main loop, where the reaction to the button press
// is processed.
void loop() {
  if (!digitalRead(buttonPin)) {
    buttonPressed = true;
    stepper.setMotorDisable();
  }else{
    if(buttonPressed){
      stepper.setMotorEnable();
      buttonPressed=false;
    }
  }
}
