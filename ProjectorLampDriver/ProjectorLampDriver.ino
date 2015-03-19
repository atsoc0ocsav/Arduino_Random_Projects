
int powerPin=9;
int enablePin=10;

boolean burning=false;
int power=255;

void setup() {
  pinMode(powerPin,OUTPUT);
  pinMode(enablePin,OUTPUT);

  analogWrite(powerPin,power);
  digitalWrite(enablePin,LOW);
  Serial.begin(9600);
  Serial.println("---- Welcome to HID Lamp Manager! ----");
  Serial.println("Command List: ");
  Serial.print(" s- Start Burning\r\n i- Increase Power\r\n d- Decrease Power\r\n e- End Burning\r\n");
  Serial.println("Developed By VC, 2013, vers. 1.5");
  Serial.println("--------------------------------------\n\n");
}

void loop() {  
  while(Serial.available()){
    char command=Serial.read();
    switch (command){
    case 's':
      if(!burning){
        burning=true;
        digitalWrite(enablePin,HIGH);
        Serial.println("Starting....");
      }
      else{
        Serial.println("Already Burning!");
      }
      break;
    case 'i':
      if(burning){
        if(power>0){
          power-=5;
          analogWrite(powerPin,power);
          Serial.print("Current Power: ");
          int powerPer=map(power,255,0,0,100);
          Serial.print(powerPer);
          Serial.println("%");
        }
        else{
          Serial.println("Already on Full Power");
        }
      }
      else{
        Serial.println("Lamp Not Burning!");
      }
      break;
    case 'd':
      if(burning){
        if(power<255){
          power+=5;
          analogWrite(powerPin,power);
          Serial.print("Current Power: ");
          int powerPer=map(power,255,0,0,100);
          Serial.print(powerPer);
          Serial.println("%");
        }
        else{
          Serial.println("Already on Minimum Power");
        }
      }
      else{
        Serial.println("Lamp Not Burning!");
      }
      break;
    case 'e':
      if(burning){
        Serial.print("Are you sure? [y/n] ");
        boolean exit=false;
        while(!exit){
          while(Serial.available()){
            char op=Serial.read();
            if(op=='y' || op=='Y'){
              digitalWrite(enablePin,LOW);
              burning=false;
              power=0;
              exit=true;
              Serial.println("Shutdown Complete!");
            }
            else{
              if(op!='n' && op!='N'){
                Serial.println("Invalid Option!");
                Serial.print("Are you sure? [y/n] ");
              }
              else{
                exit=true;
                Serial.println("Shutdown canceled!");
                break;
              }
            }
          }
        }
      }
      else{
        Serial.println("Lamp already off");
      }
      break;
    default:
      Serial.println("Invalid option");
    }
  }
}







