#include <TimerOne.h>

#include "state.h"
#include "rtc.h"
#include "sensor.h"
#include "heater.h"
#include "ui.h"

State state = {
    .screen = Screen::Menu,
    .item = Item::SetTemp
};

RTC rtc(state);
Sensor sensor(state);
Heater heater(state);
UI ui(state);

void clock1kHz() {
    ui.clock1kHz();
    heater.clock();
}

void setup(void) {

    Serial.begin(9600);

    Timer1.initialize(1000); // 1ms period (1kHz)
    Timer1.attachInterrupt(clock1kHz);

    rtc.setup();
    sensor.setup();
    heater.setup();
    ui.setup();

}

void loop(void) {

    delay(50);

    rtc.readTime();

    if (sensor.readTemperature()) {
        if (state.actualTemp < state.desiredTemp) {
            heater.setPower(50);
        } else {
            heater.setPower(0);
        }
    }

    ui.react();

    ui.render();

}
