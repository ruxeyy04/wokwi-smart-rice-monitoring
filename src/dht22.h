
#include <DHT.h>
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float lastHumid = 0;
float humid;

float lastTemp = 0;
float temp;

void initDHT()
{
  dht.begin();
}

float getHumid()
{
  humid = dht.readHumidity();

  if (isnan(humid))
  {
    Serial.println("Humidity reading is NaN, using last valid value.");
    return lastHumid;
  }
  else
  {
    lastHumid = humid;
    return humid;
  }
}

float getTemp()
{
  temp = dht.readTemperature();

  if (isnan(temp))
  {
    Serial.println("Temp reading is NaN, using last valid value.");
    return lastTemp;
  }
  else
  {
    lastTemp = temp;
    return temp;
  }
}

void displayDHTVal()
{
  display.setCursor(0, 18);
  display.print("Temp: ");
  display.print(getTemp());
  display.println("C  ");
  display.setCursor(0, 26);
  display.print("Humidity: ");
  display.print(getHumid());
  display.println("%  ");
}