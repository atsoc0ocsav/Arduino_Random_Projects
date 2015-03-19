/**********************************************
 * Returns the Orientation of the Compass at A0
 ***********************************************/

//Setup
void setup(){
  Serial.begin(9600);
}

//Loop
void loop(){
  int val = analogRead(A0);
  Serial.print("Readed value: ");
  Serial.println(val);
  val = map(val,0,795,8,1);
  Serial.print("Converted value: ");
  Serial.println(val);
  Serial.print("Orientation: ");
  Serial.println(orientation(val));
  delay(500);
}

//Returns the String of the orientation 
//according to the given value
String orientation(int value){
  switch(value){
  case 1:
    return("Este\n");
  case 2:
    return("Sudeste\n");
  case 3:
    return("Sul\n");
  case 4:
    return("Sudoeste\n");
  case 5:
    return("Oeste\n");
  case 6:
    return("Nordoeste\n");
  case 7:
    return("Norte\n");
  case 8:
    return("Nordeste\n");
  default:
    return("Erro\n");
  }
}


