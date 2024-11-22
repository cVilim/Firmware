#include "sensors.h"

SENSOR::SENSOR(std::string s_name, uint8_t pin, SENSOR_TYPE S_TYPE, float max_parameter, float max_reading, float min_reading)
    : s_name(s_name), pin(pin), S_TYPE(S_TYPE){
        if(S_TYPE == SENSOR_TYPE::PRESSURE){
            MAX_PRESSURE = max_parameter;
            MAX_READING_P = max_reading;
            MIN_READING_P = min_reading;
        }
        else if(S_TYPE == SENSOR_TYPE::TEMPERATURE){
            MAX_TEMP = max_reading;
            MAX_READING_T = max_reading;
            MIN_READING_T = min_reading;
        }
    }


float SENSOR::readData(){
    if(S_TYPE == SENSOR_TYPE::PRESSURE){
        float rawValue = analogRead(pin);
        sensorValue = ((float(rawValue) - MIN_READING_P) * MAX_PRESSURE) / (MAX_READING_P - MIN_READING_P);
    }
    else if(S_TYPE == SENSOR_TYPE::TEMPERATURE){
        //control logic for MAX31865 and mux or whatever
        Serial.println("The sensor that is initiated is a temperature sensor");
    }
    return sensorValue;
}

SENSOR_TYPE SENSOR::getType() const{
    return S_TYPE;
}

std::string SENSOR::getName() const{
    return s_name;
}
