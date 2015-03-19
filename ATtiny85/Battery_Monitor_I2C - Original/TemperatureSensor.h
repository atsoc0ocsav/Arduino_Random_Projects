#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

#define TEMPERATURE_SAMPLES 30
#define EXTREMES_RATIO 5
#define OFFSET -3

class TemperatureSensor {
    int temperatureReadings[TEMPERATURE_SAMPLES];
    int pos;
    int firstConversion;

  public:
    void init(void);
    double getTemperature_Lsb(void);
    double getTemperature_Celsius(void);
    int getTemperature_Raw(void);
};

#endif // _TEMPERATURE_SENSOR_H_
