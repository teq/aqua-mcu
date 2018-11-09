#pragma once

#include "state.h"

/** Responsible for UI rendering */
class UI {

    public:

        UI(State& appState);

        void setup(void);

        void clock1kHz(void);

        void render(void);

        void react(void);

    private:

        void renderHome(void);
        void reactHome(void);
        void renderMenu(void);
        void reactMenu(void);

        State& state;

};
