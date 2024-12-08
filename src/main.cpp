#include <Arduino.h>
#include "sensors.h"
#include "valves.h"
#include "statehandler.h"

ENGINE valkyrie(new IDLE);

SENSOR mov_s("baja", 35, SENSOR_TYPE::PRESSURE, 10.0f, 4096, 355.0f);
VALVE MOV("mov", 5, VALVE_TYPE::SERVO, 1.0f, false, false, 0.0f, 1, 0.8, 0.5, 0.2, 0);

void setup() {
    Serial.begin(9600);
}

void loop() {

    valkyrie.handle_state();
    double myTime = millis();

    if(myTime > 5000 && myTime < 10000){
        valkyrie.transition_to(new RUNNING);
        valkyrie.handle_state();
    }
    else if(myTime > 10000 && myTime < 11000){
        valkyrie.transition_to(new SHUTDOWN);
        valkyrie.handle_state();
    }
    else if(myTime > 11000){
        valkyrie.transition_to(new IDLE);
        valkyrie.handle_state();
    }


}
