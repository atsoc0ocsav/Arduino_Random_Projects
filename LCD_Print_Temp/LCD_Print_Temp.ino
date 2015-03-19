#include <LiquidCrystal.h>
#include <OneWire.h>

OneWire  ds(13);  
LiquidCrystal lcd(12, 11,9,8,7,6, 5, 4, 3, 2);
float maxTemp, minTemp;

byte degree[7]={
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000};

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.home();
  lcd.print("Wellcome");
  delay(2000);
  lcd.clear();
  lcd.print("Temperature:");
  lcd.createChar(1,degree);
  maxTemp=getTemp();
  minTemp=maxTemp;
}

void loop(void) {
  float temperature=getTemp();
  if(temperature>maxTemp) maxTemp=temperature;
  if(temperature<minTemp) minTemp=temperature;
  lcd.setCursor(0,1);
  lcd.print(minTemp);
  lcd.setCursor(6,1);
  lcd.print(temperature);
  lcd.setCursor(12,1);
  lcd.print(maxTemp);
}

float getTemp(){
  byte i;
  byte present = 0;
  byte type_s=0;
  byte data[12];
  byte addr[8];
  float celsius;
verification:
  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    goto verification;
  }
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);      
  delay(1000);
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);        
  for ( i = 0; i < 9; i++) {           
    data[i] = ds.read();
  }
  unsigned int raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  if (cfg == 0x00) raw = raw << 3; 
  else if (cfg == 0x20) raw = raw << 2;
  else if (cfg == 0x40) raw = raw << 1;
  celsius = (float)raw / 16.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.println(" Celsius, ");
  return celsius;
}

