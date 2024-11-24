

#ifndef LDR_H
#define LDR_H
#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;

void setupLDRSensor()
{
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test begin"));
}
int lux;
int getLightLevel()
{
  lux = lightMeter.readLightLevel();
  return lux;
}

void displayLux()
{
  lux = getLightLevel();
  display.setCursor(0, 34);
  display.print("Lux: ");
  display.println(lux);
}
#endif
