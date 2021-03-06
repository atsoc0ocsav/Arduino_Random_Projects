/*
 
 Example code for connecting a Parallax GPS module to the Arduino
 
 Igor Gonz�lez Mart�n. 05-04-2007
 igor.gonzalez.martin@gmail.com
 
 English translation by djmatic 19-05-2007
 
 Listen for the $GPRMC string and extract the GPS location data from this.
 Display the result in the Arduino's serial monitor.
 
 */

#include <string.h>
#include <ctype.h>

int ledPin = 13;                  // LED test pin
int rxPin = 0;                    // RX PIN 
int txPin = 1;                    // TX TX
int byteGPS=-1;
char linea[80] = "";
char comandoGPR[7] = "$GPGGA";
int cont=0;
int bien=0;
int conta=0;
int indices[15];

void setup() {
  pinMode(ledPin, OUTPUT);       // Initialize LED pin
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(38400);
  for (int i=0;i<80;i++){       // Initialize a buffer for received data
    linea[i]=' ';
  }   
}

void loop() {
  digitalWrite(ledPin, HIGH);
  byteGPS=Serial.read();         // Read a byte of the serial port
  if (byteGPS == -1) {           // See if the port is empty yet
    delay(100); 
  } 
  else {
    linea[conta]=byteGPS;        // If there is serial port data, it is put in the buffer
    conta++;                      
    Serial.write(byteGPS); 
    if (byteGPS==13){            // If the received byte is = to 13, end of transmission
      digitalWrite(ledPin, LOW); 
      cont=0;
      bien=0;
      for (int i=1;i<7;i++){     // Verifies if the received command starts with $GPR
        if (linea[i]==comandoGPR[i-1]){
          bien++;
        }
      }
      if(bien==6){               // If yes, continue and process the data
        for (int i=0;i<80;i++){
          if (linea[i]==','){    // check for the position of the  "," separator
            indices[cont]=i;
            cont++;
          }
          if (linea[i]=='*'){    // ... and the "*"
            indices[14]=i;
            cont++;
          }
        }
        Serial.println("");      // ... and write to the serial port
        Serial.println("");
        Serial.println("---------------");
        for (int i=0;i<14;i++){
          switch(i){
          case 0 :
            Serial.print("Time in UTC (HhMmSs): ");
            break;
          case 1 :
            Serial.print("Latitude: ");
            break;
          case 2 :
            Serial.print("Latitude Direction (N/S): ");
            break;
          case 3 :
            Serial.print("Longitude: ");
            break;
          case 4 :
            Serial.print("Longitude Direction (E/W): ");
            break;
          case 5 :
            Serial.print("Fix Quality: ");
            break;
          case 6 :
            Serial.print("Number of satellites: ");
            break;
          case 7 :
            Serial.print("Horizontal dilution position: ");
            break;
          case 8 :
            Serial.print("Altitude: ");
            break;
          case 9 :
            Serial.print("Altitude Measure: ");
            break;
          case 10 :
            Serial.print("Height of geoid: ");
            break;
          case 11 :
            Serial.print("Heigth Measure: ");
            break;
          case 12 :
            Serial.print("Time since last DGPS update: ");
            break;
          case 13 :
            Serial.print("DGPS Station ID number: ");
            break;
          case 14 :
            Serial.print("Checksum: ");
            break;
          }
          for (int j=indices[i];j<(indices[i+1]-1);j++){
            Serial.print(linea[j+1]); 
          }
          Serial.println("");
        }
        Serial.println("---------------");
      }
      conta=0;                    // Reset the buffer
      for (int i=0;i<80;i++){    //  
        linea[i]=' '; 
      }                 
    }
  }
  if(conta>=80){
    conta=0;                    // Reset the buffer
    for (int i=0;i<80;i++){    //  
      linea[i]=' '; 
    }
    Serial.println("");
  }
}


