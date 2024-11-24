#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

void welcome() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor((128 - (6 * 10)) / 2, 10);
  display.println("Welcome to");

  display.setCursor((128 - (6 * 10)) / 2, 25);
  display.println("Smart Rice");

  display.setCursor((128 - (6 * 17)) / 2, 40);
  display.println("Monitoring System");

  display.display();
  delay(5000);

  display.clearDisplay();
  display.display();
}