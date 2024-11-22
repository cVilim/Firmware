#include <Arduino.h>
#include "sensors.h"
#include "valves.h"

SENSOR mov_s("mov_sensor", 35, SENSOR_TYPE::PRESSURE, 10.0f, 4096, 355.0f);
VALVE MOV("MOV", 5, VALVE_TYPE::SERVO, 10.0f, false, false, 90.0f, 0.0f, 0.0f, 0.0f);

void setup() {
    Serial.begin(9600);
    MOV.VALVE_TO_IDLE();
}

void loop() {
    MOV.VALVE_FULLY_OPEN();
    delay(1000);
    MOV.VALVE_CLOSE();
    delay(1000);
}

