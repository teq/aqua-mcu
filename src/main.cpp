#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TimerOne.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5);

void setHeaterPower(uint8_t value) {
  uint16_t duty = 1024 - 1024 * (value / 255.0);
  Timer1.setPwmDuty(9, duty);
}

void setup(void) {

  Serial.begin(9600);

  sensors.begin();

  display.begin();
  display.setContrast(55);

  Timer1.initialize(500000);
  Timer1.pwm(9, 1024); // off

}

void loop(void) {

  delay(500);

  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  display.clearDisplay();
  display.print("Temp: ");
  display.println(temp);
  display.display();

  Serial.print("Temp: ");
  Serial.println(temp);

}
