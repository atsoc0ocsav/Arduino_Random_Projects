#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11,9,8,7,6, 5, 4, 3, 2);
char charArray[32] = {
  "Wellcome"};
int pointer = 1;
int serial=0;

void setup() { 
  lcd.begin(16,2);
  Serial.begin(9600); 
  lcd.print(charArray);
}

//Receives chars on Serial and prints it on the LCD
void loop() {
  serial=0;
  int j=0;
  lcd.setCursor(0,pointer);
  lcd.blink();
  for(int i=0;i<32;i++){
    charArray[i]=' ';
  }
  while(Serial.available()>0){
    charArray[j] = Serial.read();
    j++;
    serial=1;
  }
  if(serial==1 && j<=16){
    Serial.println(charArray);
    writeLcd(charArray);
    if(pointer==1)
      pointer=0;
    else 
      pointer=1;
  }
  delay(200);
}

// Write the charArray on the LCD
void writeLcd(char* chars){
  lcd.setCursor(0,pointer);
  lcd.write(chars);
}










