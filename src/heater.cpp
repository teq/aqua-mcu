#include <Arduino.h>

#include "heater.h"

#define HEATER_PIN 9
#define PERIOD_TICKS 1000

Heater::Heater(State& appState):
    state(appState),
    tickCount(1),
    endTick(0)
{ }

void Heater::setup(void) {
    pinMode(HEATER_PIN, OUTPUT);
    setPower(0);
}

void Heater::tick(void) {

    if (endTick < tickCount) {
        digitalWrite(HEATER_PIN, HIGH); // off
    } else {
        digitalWrite(HEATER_PIN, LOW); // on
    }

    if (++tickCount > PERIOD_TICKS) {
        tickCount = 1;
    }

}

void Heater::setPower(uint8_t heaterPower) {
    float dutyCycle = heaterPower / 100.0;
    endTick = PERIOD_TICKS * dutyCycle;
    state.heaterPower = heaterPower;
}
