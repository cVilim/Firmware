#ifndef VALVES_H
#define VALVES_H

#include <string>
#include <Arduino.h>
#include "ESP32Servo.h"

enum class VALVE_TYPE{
    SOLENOID,
    SERVO
};

class VALVE{
private:
    std::string v_name;
    uint8_t v_pin;
    VALVE_TYPE V_TYPE;

    Servo VSERVO;
    
    float NOMINAL_PRESSURE;
    float PRESSURE_AT_VALVE;

    float defaultAngle;
    float currentAngle;

    const bool DEFAULT_IS_OPEN;
    bool IS_OPEN;

    float KI = 0.0f;
    float KP = 0.0f;
    float KD = 0.0f;

    float integral;
    float prevError;

    unsigned long lastUpdateTime;

public:
    VALVE(std::string v_name, uint8_t v_pin, VALVE_TYPE V_TYPE, float NOMINAL_PRESSURE, bool IS_OPEN, const bool DEFAULT_IS_OPEN, float defaultAngle, float KI, float KP, float KD);
    

    void SERVO_VALVE_CONTROL(float P_CURRENT);
    void VALVE_TO_IDLE();
    void VALVE_FULLY_OPEN();
    void VALVE_CLOSE();
    void VALVE_TO(float angle);

};

#endif