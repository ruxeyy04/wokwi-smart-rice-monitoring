#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <BH1750.h>
#include "welcome.h"
#include "wifiSetup.h"
#include "ph.h"
#include "ldr.h"
#include "dht22.h"
#include "moisture.h"
#include "ultrasonic.h"

// OLED dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
    Serial.begin(115200);

    welcome();
    wifiSetup();
    setupLDRSensor();
    initDHT();
    initUltrasonic();
    delay(2000); // Display splash screen
}

void loop()
{
    display.clearDisplay();
    analyzeGate();
    displayDHTVal();
    displayLux();
    ph_Sensor();
    displayMoistureLevel();
    display.display();

    delay(500); // Wait for 2 seconds before next reading
}
