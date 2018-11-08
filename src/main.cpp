#include <TimerOne.h>
#include <ClickEncoder.h>

#include "state.h"
#include "rtc.h"
#include "sensor.h"
#include "heater.h"
#include "ui.h"

State state = {
    .screen = Screen::Home,
    .item = Item::SetTemp
};

RTC rtc(state);
Sensor sensor(state);
Heater heater(state);
UI ui(state);
ClickEncoder encoder(A0, A1, -1, 1);

void clock1kHz() {
    encoder.service();
    heater.tick();
}

void setup(void) {

    Serial.begin(9600);

    Timer1.initialize(1000); // 1ms
    Timer1.attachInterrupt(clock1kHz);
    encoder.setAccelerationEnabled(true);

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

    ui.render();


    // int16_t encVal = encoder.getValue();
    // display.print("Enc:");
    // display.println(encVal);

}
