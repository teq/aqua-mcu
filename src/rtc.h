#pragma once

#include <stdint.h>

#include "state.h"

class RTC {

    public:

        RTC(State& appState);

        void setup(void);

        bool readTime(bool throttle = true);


    private:

        State& state;

};
