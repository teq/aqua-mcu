#pragma once

#include "state.h"

/** Responsible for UI rendering */
class UI {

    public:

        UI(const State& appState);

        void setup(void);

        void render(void);

    private:

        const State& state;

};
