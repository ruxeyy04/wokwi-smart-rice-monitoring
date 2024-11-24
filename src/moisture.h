#ifndef MOISTURE_H
#define MOISTURE_H
#include <Arduino.h>
#define MoisturePin 34 
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

int moisture;

int getMoistureLevel() {
  int moistureValue = analogRead(MoisturePin);  
  int moisturePercent = map(moistureValue, 4095, 2, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);
  return moisturePercent;
}

void displayMoistureLevel() {
  moisture = getMoistureLevel();
  display.setCursor(0, 50);  
  display.print("Moisture: ");
  display.print(moisture);
  display.println("%");
}
#endif
