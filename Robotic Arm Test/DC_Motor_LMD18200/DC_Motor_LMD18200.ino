
int dirPIN=3;
int pwmPIN=5;
int brkPIN=4;
int swtchPIN=8;

int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input 
int button = LOW;
int dir=LOW;

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;

void setup(){
  pinMode(dirPIN,OUTPUT);
  pinMode(brkPIN,OUTPUT);
  pinMode(pwmPIN,OUTPUT);
  pinMode(swtchPIN,INPUT);
  Serial.begin(9600);
}

void loop(){
  int pot =map(analogRead(A0),0,1023,0,255);
  
  digitalWrite(brkPIN,LOW);
  
  int lastState=buttonState;
  buttonState=digitalRead(swtchPIN);
  Serial.println(buttonState);
  if(buttonState!=lastState && buttonState){
    button=!button;
    Serial.println(buttonState);
  }
  //digitalWrite(dirPIN,buttonState);
  
  digitalWrite(dirPIN,button);
  Serial.print("Pot: ");
  Serial.println(pot);
  Serial.print("Dir: ");
  if(button)
    Serial.println("Direita");
  else
    Serial.println("Esquerda");
  analogWrite(pwmPIN,pot);
  delay(100);
  
  
  
  
}


