#include <Arduino.h>
#include "sensors.h"
#include "valves.h"

SENSOR mov_s("baja", 35, SENSOR_TYPE::PRESSURE, 10.0f, 4096, 355.0f);

void setup() {
    Serial.begin(9600);
}

void loop() {

}

