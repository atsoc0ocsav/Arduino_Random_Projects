
int dirAPIN=3;
int pwmAPIN=5;
int brkAPIN=4;

int dirBPIN=7;
int pwmBPIN=6;
int brkBPIN=8;

int swtchPIN=9;

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input 
int button = LOW;
int dir=LOW;

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;

int n=0;

void setup(){
  pinMode(dirAPIN,OUTPUT);
  pinMode(brkAPIN,OUTPUT);
  pinMode(pwmAPIN,OUTPUT);
  pinMode(dirBPIN,OUTPUT);
  pinMode(brkBPIN,OUTPUT);
  pinMode(pwmBPIN,OUTPUT);
  pinMode(swtchPIN,INPUT);
  Serial.begin(9600);
}

void loop(){
  //int pot=map(analogRead(A0),0,1023,0,255);
  int pot=255;
  int delayy=950;

  /*
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
   Serial.println("Esquerda");*/
  if(n<1000){
    digitalWrite(brkAPIN,HIGH);
    digitalWrite(brkBPIN,LOW);
    digitalWrite(dirAPIN,HIGH);
    analogWrite(pwmAPIN,pot);
    //delay(delayy);
    delayMicroseconds(delayy); 

    digitalWrite(brkAPIN,LOW);
    digitalWrite(brkBPIN,HIGH);
    digitalWrite(dirBPIN,HIGH);
    analogWrite(pwmBPIN,pot);
    //delay(delayy); 
    delayMicroseconds(delayy); 

    digitalWrite(brkAPIN,HIGH);
    digitalWrite(brkBPIN,LOW);
    digitalWrite(dirAPIN,LOW);
    analogWrite(pwmAPIN,pot);
    //delay(delayy); 
    delayMicroseconds(delayy); 

    digitalWrite(brkAPIN,LOW);
    digitalWrite(brkBPIN,HIGH);
    digitalWrite(dirBPIN,LOW);
    analogWrite(pwmBPIN,pot);
    //delay(delayy);
    delayMicroseconds(delayy); 
  }

  else{  
    digitalWrite(brkAPIN,LOW);
    digitalWrite(brkBPIN,HIGH);
    digitalWrite(dirBPIN,LOW);
    analogWrite(pwmBPIN,pot);
    //delay(delayy);
    delayMicroseconds(delayy);

    digitalWrite(brkAPIN,HIGH);
    digitalWrite(brkBPIN,LOW);
    digitalWrite(dirAPIN,LOW);
    analogWrite(pwmAPIN,pot);
    //delay(delayy); 
    delayMicroseconds(delayy); 

    digitalWrite(brkAPIN,LOW);
    digitalWrite(brkBPIN,HIGH);
    digitalWrite(dirBPIN,HIGH);
    analogWrite(pwmBPIN,pot);
    //delay(delayy); 
    delayMicroseconds(delayy); 

    digitalWrite(brkAPIN,HIGH);
    digitalWrite(brkBPIN,LOW);
    digitalWrite(dirAPIN,HIGH);
    analogWrite(pwmAPIN,pot);
    //delay(delayy);
    delayMicroseconds(delayy); 

    if(n>2000)
      n=0;
  }

  n++;

  /*
  digitalWrite(pwmAPIN,LOW);
   digitalWrite(dirAPIN,HIGH);
   digitalWrite(brkAPIN,LOW);
   
   
   digitalWrite(pwmBPIN,LOW);
   digitalWrite(dirBPIN,HIGH);
   digitalWrite(brkBPIN,LOW);
   */
}




