#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include <string>
#include <vector>

enum class SENSOR_TYPE{
    TEMPERATURE,
    PRESSURE
};

class SENSOR{
private:
    std::string s_name;
    uint8_t pin;
    SENSOR_TYPE S_TYPE;

    float MAX_PRESSURE = 0.0f;
    float MAX_READING_P = 0.0f;
    float MIN_READING_P = 0.0f;

    float MAX_TEMP = 0.0f;
    float MAX_READING_T = 0.0f;
    float MIN_READING_T = 0.0f;

    float sensorValue = 0;

public:
    SENSOR(std::string s_name, uint8_t pin, SENSOR_TYPE S_TYPE, float max_parameter, float max_reading, float min_reading);

    float readData();
    SENSOR_TYPE getType() const;
    std::string getName() const;
};

#endif