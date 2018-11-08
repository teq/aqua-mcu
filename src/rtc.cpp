#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

#include "rtc.h"

PCF8583 pcf8583;

uint32_t lastRead;

RTC::RTC(State& appState):
    state(appState)
{ }

void RTC::setup(void) {

    Wire.begin();
    pcf8583.begin();

    readTime(false);

    // if (! rtc.isrunning()) {
    //     Serial.println("RTC is NOT running!");
    //     // rtc.adjust(DateTime(__DATE__, __TIME__));
    // }
    // else
    // {
    //     Serial.println("RTC OK");
    //     // DateTime now = DateTime(2018, 11, 7, 10, 55, 0);
    //     // rtc.adjust(now);
    // }

}

bool RTC::readTime(bool throttle) {

    // Wait at least 1 sec between readings
    if (throttle && (millis() - lastRead) < 1000) return false;

    DateTime now = pcf8583.now();

    state.rtcDay = now.day();
    state.rtcMonth = now.month();
    state.rtcYear = now.year();
    state.rtcHour = now.hour();
    state.rtcMinute = now.minute();
    state.rtcSecond = now.second();

    lastRead = millis();

    return true;

}
