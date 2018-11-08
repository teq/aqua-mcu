#pragma once

#include <stdint.h>

#include "state.h"

/** Represents a heater controlled by PWM */
class Heater {

    public:

        Heater(State& appState);

        /** Setup PWM pin */
        void setup(void);

        /** Trigger PWM tick */
        void tick(void);

        /**
         * Set heater power
         * @param heaterPower Power in percents (0-100)
         */
        void setPower(uint8_t heaterPower);

    private:

        State& state;
        uint16_t tickCount;
        volatile uint16_t endTick;

};
