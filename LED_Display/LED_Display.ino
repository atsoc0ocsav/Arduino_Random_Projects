
int intensityPin=11;
int pwmIntensity=0;
int hundredChar=10;
int testDisplayPin=12;
int start=0;
int count=0;
int limit=199;

void setup(){
  pinMode(pwmIntensity,OUTPUT);
  pinMode(hundredChar,OUTPUT);
  pinMode(testDisplayPin,OUTPUT);
  testDisplay();
  int i;
  for(i=2;i<10;i++)
    pinMode(i,OUTPUT);
}

void loop(){
  digitalWrite(hundredChar,HIGH);
  pwmIntensity=map(analogRead(A0),0,1023,0,255);
  analogWrite(intensityPin,pwmIntensity);
  if(count>limit)
    count=start;
  printNums();
  count++;
  delay(100);
}

void testDisplay(){
  digitalWrite(testDisplayPin,LOW);
  analogWrite(hundredChar,25);
  delay(5000);
  digitalWrite(testDisplayPin,HIGH);
  analogWrite(hundredChar,0);
  
}

void printNums(){
  byte unitsBin[4];
  byte dozensBin[4];
  int dozens=int(count/10);
  if(dozens>=10)
    dozens-=10;
  int units=count-int(count/10)*10;
  integerToBits(units,unitsBin);
  integerToBits(dozens,dozensBin);
  if(int(count/100)!=0)
    analogWrite(hundredChar,map(pwmIntensity,0,255,255,0));
  int i;
  for(i=0;i<4;i++)
    digitalWrite(5-i,unitsBin[i]);
  for(i=0;i<4;i++)
    digitalWrite(9-i,dozensBin[i]);
} 

void integerToBits (int value, byte b[]) {
  b[0] = (byte)(1 &&(value & B00001000));
  b[1] = (byte)(1 &&(value & B00000100));
  b[2] = (byte)(1 &&(value & B00000010));
  b[3] = (byte)(1 &&(value & B00000001));
}
