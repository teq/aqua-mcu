#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TimerOne.h>
#include <PinChangeInterrupt.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5);

volatile float desiredTemp = 27.0;
float actualTemp = 0;
uint8_t heat = 0;

void setHeaterPower(uint8_t value) {
    heat = value;
    uint16_t duty = 1024 - 1024 * (value / 255.0);
    Timer1.setPwmDuty(9, duty);
}

void encoderClick(void) {
    if (digitalRead(A1)) {
        desiredTemp += 0.10;
    } else {
        desiredTemp -= 0.10;
    }
}

void setup(void) {

    Serial.begin(9600);

    // sensors.setWaitForConversion(false);
    sensors.begin();

    display.begin();
    display.setContrast(55);

    Timer1.initialize(500000);
    Timer1.pwm(9, 1024); // off

    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    attachPCINT(digitalPinToPCINT(A0), encoderClick, FALLING);

}

void loop(void) {

    // delay(500);

    sensors.requestTemperatures();
    actualTemp = sensors.getTempCByIndex(0);

    if (actualTemp < desiredTemp) {
        setHeaterPower(127);
    } else {
        setHeaterPower(0);
    }

    display.clearDisplay();
    display.print("Des:");
    display.println(desiredTemp);
    display.print("Act: ");
    display.println(actualTemp);
    display.print("Heat: ");
    display.println(heat);
    display.display();

}
