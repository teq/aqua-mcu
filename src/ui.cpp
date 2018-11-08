#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include <Fonts/FreeSerifBold18pt7b.h>

#include "ui.h"

Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5);

UI::UI(const State& appState):
    state(appState)
{ }

void UI::setup(void) {
    display.begin();
    display.setContrast(55);
}

void UI::render(void) {

    display.clearDisplay();
    display.setFont(NULL);
    display.setCursor(0, 0);

    display.print("Temp:");
    display.println(state.actualTemp);
    display.print("Des:");
    display.println(state.desiredTemp);
    display.print("Pow:");
    display.println(state.heaterPower);

    // display.setFont(&FreeSerifBold18pt7b);

    display.print("Time:");
    display.print(state.rtcHour);
    display.print(":");
    display.print(state.rtcMinute);
    display.print(":");
    display.println(state.rtcSecond);

    display.display();

}
