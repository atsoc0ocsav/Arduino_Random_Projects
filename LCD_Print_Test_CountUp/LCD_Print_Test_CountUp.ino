#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() { 
  lcd.begin(16,2);
}

void loop() {
  lcd.setCursor(0, 0);
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    delay(200);
  }
  lcd.setCursor(0,1);
  lcd.noAutoscroll();
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    delay(200);
  }
  lcd.clear();
}


