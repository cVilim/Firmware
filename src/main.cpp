#include <Arduino.h>
#include "sensors.h"
#include "valves.h"
#include "statemanager.h"

SENSOR mov_s("baja", 35, SENSOR_TYPE::PRESSURE, 10.0f, 4096, 355.0f);
VALVE MOV("mov", 5, VALVE_TYPE::SERVO, 1.0f, false, false, 0.0f, 1, 0.8, 0.5, 0.2, 0);

STATE_HANDLER valkyrie;     //handle the engine with the name valkyrie

void setup() {
    Serial.begin(9600);
    valkyrie.setState(std::make_shared<IDLE>());

}

void loop() {
    MOV.SERVO_VALVE_CONTROL(mov_s.readData());
    delay(5);
}
