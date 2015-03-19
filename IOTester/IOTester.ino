int valvesPins[32] = {  A0,  A1,  A2, A3, A4, A5, A6, A7,
                         2,   3,   4,  5,  6, 10,  8,  7,
                        14,  32,  15, 30, 16, 28, 17, 26,
                       A11, A12, A10, 50, A9, 48, A8, 46
                     };


int current = 0;

void setup() {
  for (int i = 0; i < 32; i++) {
    pinMode(valvesPins[i], OUTPUT);
    digitalWrite(valvesPins[i], LOW);
  }

  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    Serial.read();
    
    if (current != 0) {
      digitalWrite(valvesPins[current - 1], LOW);
    }

    digitalWrite(valvesPins[current], HIGH);

    Serial.print("Current: ");
    Serial.print(current);
    Serial.print("		Pin: ");
    Serial.print(valvesPins[current]);
    Serial.println();

    current++;
    if (current == 32) {
      current = 0;
    }
    
  }
}
