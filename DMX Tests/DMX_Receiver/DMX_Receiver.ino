#include <lib_dmx.h>

void setup()
{
  ArduinoDmx0.set_control_pin(2);    // Arduino output pin for MAX485 input/output control (connect to MAX485 pins 2-3)
  ArduinoDmx0.set_rx_address(1);      // set rx0 dmx start address
  ArduinoDmx0.set_rx_channels(3);     // number of rx channels
  ArduinoDmx0.init_rx(0);        // starts universe 0 as rx, NEW Parameter DMX mode

}

void loop()
{
  analogWrite(3, ArduinoDmx0.RxBuffer[0]);
  analogWrite(5, ArduinoDmx0.RxBuffer[1]);
  analogWrite(6, ArduinoDmx0.RxBuffer[2]);
}  //end loop()

