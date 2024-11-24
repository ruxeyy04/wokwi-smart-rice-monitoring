#include <Arduino.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

#define TRIG_PIN_1 4   // Trigger pin for ultrasonic 1
#define ECHO_PIN_1 13  // Echo pin for ultrasonic 1
#define TRIG_PIN_2 12  // Trigger pin for ultrasonic 2
#define ECHO_PIN_2 27  // Echo pin for ultrasonic 2
#define RELAY_PIN 2   // Relay control pin for gate

long duration1, duration2;
int distance1, distance2;

long getDistance(int trigPin, int echoPin)
{
    // Send a 10µs pulse to trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the duration of the echo pulse
    long duration = pulseIn(echoPin, HIGH);

    // Calculate the distance (in cm)
    long distance = duration * 0.0344 / 2;
    return distance;
}

void initUltrasonic()
{
    pinMode(TRIG_PIN_1, OUTPUT);
    pinMode(ECHO_PIN_1, INPUT);
    pinMode(TRIG_PIN_2, OUTPUT);
    pinMode(ECHO_PIN_2, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);  // Turn off relay initially
}

// Function to calculate water level percentage
int calculateWaterLevelPercent(long distance)
{
    // Empty distance = 200 cm, Full distance = 2 cm
    long minDistance = 2;   // Full tank distance in cm
    long maxDistance = 200; // Empty tank distance in cm

    // Calculate the percentage (100% = full, 0% = empty)
    int waterLevelPercent = map(distance, minDistance, maxDistance, 100, 0);
    
    // Ensure the value is within valid bounds (0 to 100%)
    waterLevelPercent = constrain(waterLevelPercent, 0, 100);
    
    return waterLevelPercent;
}

void analyzeGate()
{
    distance1 = getDistance(TRIG_PIN_1, ECHO_PIN_1);
    distance2 = getDistance(TRIG_PIN_2, ECHO_PIN_2);

    int waterLevel1 = calculateWaterLevelPercent(distance1);  // Water level in percent for ultrasonic 1
    int waterLevel2 = calculateWaterLevelPercent(distance2);  // Water level in percent for ultrasonic 2

    display.setCursor(0, 0);
    display.print("Ultrasonic 1: ");
    display.print(waterLevel1);
    display.println("%");
    display.print("Ultrasonic 2: ");
    display.print(waterLevel2);
    display.println("%");

    // If both ultrasonic sensors have 0% water level, do not turn on the relay
    if (waterLevel1 == 0 && waterLevel2 == 0)
    {
        Serial.println("Waiting for Ultrasonic 1 to fill");
        digitalWrite(RELAY_PIN, LOW);  
    }
    else if (waterLevel1 >= 90 && waterLevel2 <= 10)  // Relay ON when 1st is full and 2nd is empty
    {
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("Relay ON");
    }
    else if (waterLevel2 <= 10)  // Relay ON when 2nd is empty
    {
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("Relay ON");
    }
    else if (waterLevel2 >= 90)  // Relay OFF when 2nd is full
    {
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Relay OFF");
    }
    else
    {
        digitalWrite(RELAY_PIN, LOW);  // Ensure relay is OFF if no conditions are met
        Serial.println("Relay OFF");
    }

}
