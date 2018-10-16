#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10);

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  display.begin();
  display.setContrast(55);
  display.display(); // show splashscreen
  delay(2000);
}

void loop(void)
{

  delay(1000);

  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  display.clearDisplay();
  display.print("Temp: ");
  display.println(temp);
  display.display();

  Serial.print("Temp: ");
  Serial.println(temp);

}
