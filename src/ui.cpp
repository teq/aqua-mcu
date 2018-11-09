#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ClickEncoder.h>

#include <Fonts/FreeSerifBold18pt7b.h>

#include "ui.h"

Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5);
ClickEncoder encoder(A0, A1, -1, 1);

void format2(char *buf, uint8_t val, uint8_t max) {
    if (val > max) {
        buf[0] = 'E';
        buf[1] = 'E';
    } else {
        buf[0] = '0' + val / 10;
        buf[1] = '0' + val % 10;
    }
}

void invert(bool flag) {
    if (flag) {
        display.setTextColor(WHITE, BLACK);
    } else {
        display.setTextColor(BLACK, WHITE);
    }
}

UI::UI(State& appState):
    state(appState)
{ }

void UI::setup(void) {
    display.begin();
    display.setContrast(55);
    encoder.setAccelerationEnabled(true);
}

void UI::clock1kHz(void) {
    encoder.service();
}

void UI::render(void) {

    display.clearDisplay();
    display.setFont(NULL);
    display.setCursor(0, 0);

    switch (state.screen) {

        case Screen::Menu:
            renderMenu();
            break;

        default:
        case Screen::Home:
            renderHome();
            break;

    }

    display.display();

}

void UI::react(void) {

    switch (state.screen) {

        case Screen::Menu:
            reactMenu();
            break;

        default:
        case Screen::Home:
            reactHome();
            break;

    }

}

void UI::renderHome(void) {

    display.setFont(&FreeSerifBold18pt7b);
    display.setCursor(0, 24);

    char str[] = "hh:mm";
    format2(&str[0], state.rtcHour, 23);
    format2(&str[3], state.rtcMinute, 59);
    display.print(str);

    display.setFont(NULL);
    display.setCursor(0, 32);
    display.print("Temp: ");
    display.println(state.actualTemp);

}

void UI::reactHome(void) {

}

void UI::renderMenu(void) {

    display.println("Settings");
    display.drawLine(0, 8, display.width()-1, 8, BLACK);

    display.setCursor(0, 10);
    invert(state.item == Item::SetTemp); display.println("Temperature");
    invert(state.item == Item::SetLamps); display.println("Lamps");
    invert(state.item == Item::SetClock); display.println("Set Clock");
    invert(state.item == Item::MenuBack); display.println("< Back <");
    invert(false);

}

void UI::reactMenu(void) {

    int16_t newItem = state.item + encoder.getValue();

    if (newItem < SetTemp) {
        newItem = SetTemp;
    } else if (newItem > MenuBack) {
        newItem = MenuBack;
    }

    state.item = newItem;

}
