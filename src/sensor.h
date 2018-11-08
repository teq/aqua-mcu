#pragma once

#include <stdint.h>

#include "state.h"

/** Responsible for sensor reading */
class Sensor {

    public:

        Sensor(State& appState);

        void setup(void);

        bool readTemperature(bool throttle = true);

    private:

        State& state;

};
