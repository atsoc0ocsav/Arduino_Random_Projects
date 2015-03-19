int brakePin=3;
int directionPin=4;
int m1Pin=8;
int m2Pin=9;
int m3Pin=10;
int m4Pin=11;
int indicationLed=6;

void setup() {
  pinMode(brakePin,OUTPUT);
  pinMode(directionPin,OUTPUT);
  pinMode(m1Pin,OUTPUT);
  pinMode(m2Pin,OUTPUT);
  pinMode(m3Pin,OUTPUT);
  pinMode(m4Pin,OUTPUT);
  pinMode(indicationLed,OUTPUT);

  digitalWrite(brakePin,LOW);
  digitalWrite(indicationLed,LOW);
  digitalWrite(directionPin,LOW);

  Serial.begin(9600);
}

void loop() {
  int velocidade=0;
  Serial.println("             Bem-vindo ao teste do LMD18245");
  Serial.println(" a - acelerar, d - desacelerar, b - break, n - direccao");
  Serial.println("--------------------------------------------------------\n");
  Serial.print("Velocidade: ");
  Serial.println(velocidade);
  while(true){
    while(Serial.available()){
      switch(Serial.read()){
      case 'a':
        if(velocidade<15){ 
          velocidade++;
          byte veloc[4];
          integerToBits(velocidade,veloc);
          digitalWrite(m1Pin,veloc[0]);
          digitalWrite(m2Pin,veloc[1]);
          digitalWrite(m3Pin,veloc[2]);
          digitalWrite(m4Pin,veloc[3]);
          Serial.print("Velocidade Actual: ");
          Serial.println(velocidade);
        }
        else
          Serial.println("Velocidade Maxima");
        break;
      case 'd':
        if(velocidade>0){
          velocidade--;
          byte veloc[4];
          integerToBits(velocidade,veloc);
          digitalWrite(m1Pin,veloc[0]);
          digitalWrite(m2Pin,veloc[1]);
          digitalWrite(m3Pin,veloc[2]);
          digitalWrite(m4Pin,veloc[3]);
          Serial.print("Velocidade Actual: ");
          Serial.println(velocidade);
        }
        else
          Serial.println("Velocidade Minima");
        break;
      case 'b':
        digitalWrite(brakePin,!digitalRead(brakePin));
        
        Serial.println(digitalRead(brakePin) ? "Travado":"Destravado");
        break;
      case 'n':
        digitalWrite(directionPin,!digitalRead(directionPin));
        Serial.println(digitalRead(directionPin)? "Horario" : "Contra-Horario");
        break;
      default:
        Serial.println("Comando Invalido!");
        break;  
      }
    }
  }
}

void integerToBits (int value, byte b[]) {
  b[3] = (byte)(1 &&(value & B00001000));
  b[2] = (byte)(1 &&(value & B00000100));
  b[1] = (byte)(1 &&(value & B00000010));
  b[0] = (byte)(1 &&(value & B00000001));
}











