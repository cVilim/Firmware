#include <Arduino.h>
#include "sensors.h"

SENSOR mov("baja", 32, SENSOR_TYPE::PRESSURE, 10.0f, 4096, 355.0f);
SENSOR mfv("baza", 36, SENSOR_TYPE::TEMPERATURE, 10.0f, 4096, 355.0f);

void setup() {
    Serial.begin(9600);
}

void loop() {
    delay(1000);
}
