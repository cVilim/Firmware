#include "valves.h"

VALVE::VALVE(std::string v_name, uint8_t v_pin, VALVE_TYPE V_TYPE, float NOMINAL_PRESSURE, bool IS_OPEN, const bool DEFAULT_IS_OPEN, float defaultAngle, float KI, float KP, float KD)
    : v_name(v_name), v_pin(v_pin), V_TYPE(V_TYPE), NOMINAL_PRESSURE(NOMINAL_PRESSURE), IS_OPEN(IS_OPEN),
     DEFAULT_IS_OPEN(DEFAULT_IS_OPEN), defaultAngle(defaultAngle), KI(KI), KP(KP), KD(KD){

    if(V_TYPE == VALVE_TYPE::SERVO){
        this->currentAngle = defaultAngle;  //stavlja trenutni kut nek bude default
    }
    else if(V_TYPE == VALVE_TYPE::SOLENOID){
        this-> IS_OPEN = DEFAULT_IS_OPEN;       //stavlja da solenoid u pocetno stanje DEFAULT_IS_OPEN
    }
}
//na main funkciji stavim za parametre da bude ocitanje od nekog senzora tipa na MOV ventil ide "MOV_S.readData()"" senzor, i to sve u loop ide
void VALVE::SERVO_VALVE_CONTROL(float P_CURRENT){
    if(V_TYPE == VALVE_TYPE::SERVO){
        unsigned long currentTime = millis();
        float dT = (currentTime - lastUpdateTime)/1000.0f;
        lastUpdateTime = currentTime;
        
        float difference = P_CURRENT - NOMINAL_PRESSURE;
        float p_term = KP * difference;
        float d_term = KD * (difference - prevError) / dT;
        integral += difference * dT;
        float i_term = KI * integral;

        float CTRL_OUTPUT = p_term + i_term + d_term;

        if(V_TYPE == VALVE_TYPE::SERVO){
            currentAngle = constrain(currentAngle + CTRL_OUTPUT, 0.0f, 90.0f);
            VSERVO.write(currentAngle);
        }

        Serial.println(CTRL_OUTPUT);

        prevError = difference;
    }
}

void VALVE::VALVE_TO_IDLE(){
    if(V_TYPE == VALVE_TYPE::SERVO){
        currentAngle = defaultAngle;    //postavlja na default angle
        pinMode(v_pin, OUTPUT);
        VSERVO.write(currentAngle);
    }
    else if(V_TYPE == VALVE_TYPE::SOLENOID){
        if(IS_OPEN != DEFAULT_IS_OPEN){     //ako je default otvorena i otvorena je, nist se ne događa, a ako je default zatvorena a otvorena je, zatvara se i suprotno
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
        currentAngle = 90;      //suprotno od close, za sad je 90 - mozda bu 0
        pinMode(v_pin, OUTPUT);
        VSERVO.write(currentAngle);
    }
    else if(V_TYPE == VALVE_TYPE::SOLENOID){
        digitalWrite(v_pin, HIGH);
    }
}

void VALVE::VALVE_CLOSE(){
    if(V_TYPE == VALVE_TYPE::SERVO){
        currentAngle = 0; //ovisi kak postavim servo, vjerojatno bude trebalo mijenjati posle
        pinMode(v_pin, OUTPUT);
        VSERVO.write(currentAngle);
    }
    else if(V_TYPE == VALVE_TYPE::SOLENOID){
        digitalWrite(v_pin, LOW);   //isto ovisi dal je ventil normalno otvoren il normalno zatvoren (vjv bu normalno zatvoren)
    }
}