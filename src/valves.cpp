#include "valves.h"

VALVE::VALVE(std::string v_name, uint8_t v_pin, VALVE_TYPE V_TYPE, float NOMINAL_PRESSURE, bool IS_OPEN, const bool DEFAULT_IS_OPEN, float defaultAngle, float KI, float KP, float KD)
    : v_name(v_name), v_pin(v_pin), V_TYPE(V_TYPE), NOMINAL_PRESSURE(NOMINAL_PRESSURE), IS_OPEN(IS_OPEN),
     DEFAULT_IS_OPEN(DEFAULT_IS_OPEN), defaultAngle(defaultAngle), KI(KI), KP(KP), KD(KD){

    if(V_TYPE == VALVE_TYPE::SERVO){
        VSERVO.attach(v_pin);
        this->currentAngle = defaultAngle; 
        VSERVO.write(currentAngle);
    }
    else if(V_TYPE == VALVE_TYPE::SOLENOID){
        this-> IS_OPEN = DEFAULT_IS_OPEN;       //sets the solenoid to the default state
    }
}

void VALVE::SERVO_VALVE_CONTROL(float P_CURRENT){
    if(V_TYPE == VALVE_TYPE::SERVO){

        VSERVO.write(P_CURRENT);

    }
}

void VALVE::VALVE_TO_IDLE(){
    if(V_TYPE == VALVE_TYPE::SERVO){
        currentAngle = defaultAngle;
        VSERVO.write(currentAngle);
    }
    else if(V_TYPE == VALVE_TYPE::SOLENOID){
        if(IS_OPEN != DEFAULT_IS_OPEN){
            IS_OPEN = DEFAULT_IS_OPEN;

            if(DEFAULT_IS_OPEN){
                digitalWrite(v_pin, HIGH);
            }
            else{
                digitalWrite(v_pin, LOW);
            }
        }
    }
}

void VALVE::VALVE_FULLY_OPEN(){
    if(V_TYPE == VALVE_TYPE::SERVO){
        currentAngle = 90;      //opposite of close, for now it is 90deg but it depends on how I will mount the servo onto the valve
        VSERVO.write(currentAngle);
    }
    else if(V_TYPE == VALVE_TYPE::SOLENOID){
        digitalWrite(v_pin, HIGH);
    }
}

void VALVE::VALVE_CLOSE(){
    if(V_TYPE == VALVE_TYPE::SERVO){
        currentAngle = 0; //depends on servo position
        VSERVO.write(currentAngle);
    }
    else if(V_TYPE == VALVE_TYPE::SOLENOID){
        digitalWrite(v_pin, LOW);   //depends if the solenoid is NO or NC
    }
}

void VALVE::VALVE_TO(float angle){
    if(V_TYPE == VALVE_TYPE::SERVO){
        VSERVO.write(angle);
    }
}
