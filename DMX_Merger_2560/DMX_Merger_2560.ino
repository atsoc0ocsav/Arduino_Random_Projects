#include <lib_dmx.h>

#define    DMX512     (0)    // (250 kbaud - 2 to 512 channels) Standard USITT DMX-512
#define    DIP_SWITCH_SIZE  10

/********************** Pins Definition *******************/
int controlPinDMX1 = 20;
int controlPinDMX2 = 6;
int controlPinDMX3 = 38;
int led1Pin = 46;
int led2Pin = 44;

int dipSwitch[DIP_SWITCH_SIZE] = {A0, A2, A4, A6, A8, A10, A12, A14, 22, 24};
/******************** Pins Definition End ****************/

int mode = -1; //0- HTP (Highest Takes priority), 1-Join Universes
int middleAddr = -1;

void setup() {
  for (int i = 0; i < DIP_SWITCH_SIZE; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

  setupMode();

  //Serial1.begin(115200);

  ArduinoDmx3.set_control_pin(controlPinDMX3);
  ArduinoDmx3.set_tx_address(1);
  ArduinoDmx3.set_tx_channels(512);
  ArduinoDmx3.init_tx(DMX512);
}//end setup()

void loop() {
  switch (mode) {
    case 0: //HTP Mode
      for (int i = 0; i < 512; i++) {
        if (ArduinoDmx1.RxBuffer[i] > ArduinoDmx2.RxBuffer[i])
          ArduinoDmx3.TxBuffer[i] = ArduinoDmx1.RxBuffer[i];
        else
          ArduinoDmx3.TxBuffer[i] = ArduinoDmx2.RxBuffer[i];
      }
      break;

    case 1: //Join Universes Mode
      for (int i = 0; i < middleAddr; i++) {
        ArduinoDmx3.TxBuffer[i] = ArduinoDmx1.RxBuffer[i];
      }
      for (int i = middleAddr + 1; i < 512; i++) {
        ArduinoDmx3.TxBuffer[i] = ArduinoDmx2.RxBuffer[i];
      }
      break;

    default:
      for (int i = 0; i < 512; i++)
        ArduinoDmx3.TxBuffer[i] = 0;
      break;
  }
}  //end loop()

void setupMode() {
  if (true) { //HTP Mode
    //if (digitalRead(dipSwitch[9])) { //HTP Mode
    mode = 0;
    middleAddr = -1;
    setupDMXNormal();
  } else { //Join Universes
    mode = 1;
    middleAddr = digitalRead(dipSwitch[0]) * 1;
    middleAddr += digitalRead(dipSwitch[1]) * 2;
    middleAddr += digitalRead(dipSwitch[2]) * 4;
    middleAddr += digitalRead(dipSwitch[3]) * 8;
    middleAddr += digitalRead(dipSwitch[4]) * 16;
    middleAddr += digitalRead(dipSwitch[5]) * 32;
    middleAddr += digitalRead(dipSwitch[6]) * 64;
    middleAddr += digitalRead(dipSwitch[7]) * 128;
    middleAddr += digitalRead(dipSwitch[8]) * 256;
    setupDMXSplited();
  }
} //end setupMode()

void setupDMXNormal() {
  ArduinoDmx1.set_control_pin(controlPinDMX1);
  ArduinoDmx2.set_control_pin(controlPinDMX2);

  ArduinoDmx1.set_rx_address(1);
  ArduinoDmx2.set_rx_address(1);

  ArduinoDmx1.set_rx_channels(512);
  ArduinoDmx2.set_rx_channels(512);

  ArduinoDmx1.init_rx(DMX512);
  ArduinoDmx2.init_rx(DMX512);

  digitalWrite(led1Pin, HIGH);
} //end setupDMXNormal()

void setupDMXSplited() {
  ArduinoDmx1.set_control_pin(controlPinDMX1);
  ArduinoDmx2.set_control_pin(controlPinDMX2);

  ArduinoDmx1.set_rx_address(1);
  ArduinoDmx2.set_rx_address(middleAddr + 1);

  ArduinoDmx1.set_rx_channels(middleAddr);
  ArduinoDmx2.set_rx_channels(512 - middleAddr);

  ArduinoDmx1.init_rx(DMX512);
  ArduinoDmx2.init_rx(DMX512);

  digitalWrite(led2Pin, HIGH);
} //end setupDMXNormal()
