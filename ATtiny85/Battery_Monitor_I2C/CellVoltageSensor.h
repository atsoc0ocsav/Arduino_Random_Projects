#ifndef _CELL_VOLTAGE_SENSOR_H_
#define _CELL_VOLTAGE_SENSOR_H_

// Analog Pin for Each Cell
#define PIN_126V        0                // Cell 3
#define PIN_84V         3                // Cell 2
#define PIN_42V         2                // Cell 1

// Input correspondent to the desired voltage (TO-DO: get this better....)
#define TARGET_126V     920              // 12.6V
#define TARGET_84V      614              // 8,4V
#define TARGET_42V      305              // 4,2V

#define CELL_COUNT		3

class CellVoltageSensor {
private:
	uint8_t currentPin = -1;
	uint16_t readAnalogInput(int portNumber);

public:
	double getCellVoltage(int cell);
	double getInputVoltage(int portNumber);
	uint8_t	getCellCount(){ return CELL_COUNT; };
};
#endif // _CELL_VOLTAGE_SENSOR_H_