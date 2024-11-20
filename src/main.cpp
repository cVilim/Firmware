#include <Arduino.h>
#include "sensors.h"
#include "valves.h"

SENSOR mov_s("baja", 32, SENSOR_TYPE::PRESSURE, 10.0f, 4096, 355.0f);
VALVE MOV("mov", 19, VALVE_TYPE::SERVO, 1.0f, false, false, 0.0f, 0.4, 0.4, 0.4);

void setup() {

    Serial.begin(9600);
}

void loop() {

    MOV.SERVO_VALVE_CONTROL(mov_s.readData());
    delay(10);
}
