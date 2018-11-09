#pragma once

#include <stdint.h>

/** Defines application state */
struct State {

    // *** UI ****

    /** Currently active screen */
    uint8_t screen;
    /** Currently active screen item */
    uint8_t item;

    /// *** Real time clock ***

    uint8_t rtcDay;
    uint8_t rtcMonth;
    uint16_t rtcYear;
    uint8_t rtcHour;
    uint8_t rtcMinute;
    uint8_t rtcSecond;

    // *** Temperature sensor ****

    /** Last reading from a temperature sensor */
    float actualTemp;
    /** Timestamp of the last reading from a temperature sensor */
    uint32_t lastActualTemp;
    /** Desired temperature */
    float desiredTemp;

    // *** Heater ***

    /** PWM duty cycle for the heater */
    uint8_t heaterPower;

    // *** Light ****

};

enum Screen {
    Home,
    Menu
};

enum Item {
    // *** Menu screen ***
    SetTemp,
    SetLamps,
    SetClock,
    MenuBack
};
