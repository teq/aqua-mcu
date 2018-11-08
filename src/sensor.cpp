#include <Arduino.h>
#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "sensor.h"

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

Sensor::Sensor(State& appState):
    state(appState)
{ }

void Sensor::setup(void) {

    sensors.begin();

    // Fetch first temperature reading synchronously
    sensors.requestTemperatures();
    state.actualTemp = sensors.getTempCByIndex(0);
    state.lastActualTemp = millis();

    // All subsequent readings are asynchronous
    sensors.setWaitForConversion(false);
    sensors.requestTemperatures();

}

bool Sensor::readTemperature(bool throttle) {

    // Wait at least 1 sec between readings
    if (throttle && (millis() - state.lastActualTemp) < 1000) return false;

    state.actualTemp = sensors.getTempCByIndex(0);
    sensors.requestTemperatures();
    state.lastActualTemp = millis();

    return true;

}
