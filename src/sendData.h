#ifndef SEND_DATA_H
#define SEND_DATA_H

#include <HTTPClient.h>
#include <ArduinoJson.h>

const String POST_API_URL = "https://xtine-rice-monitoring.bytevortexz.com/api/esp32/send_data";
const String POST_DEVICE_ID = "AGRIX00001";

bool sendData(float light, float moisture, float ph, float temp, float humid)
{
    // Prepare JSON payload
    DynamicJsonDocument doc(1024);
    doc["device_id"] = POST_DEVICE_ID;
    doc["light"] = String(light, 1);
    doc["moisture"] = String(moisture, 1);
    doc["ph"] = String(ph, 1);
    doc["temp"] = String(temp);
    doc["humid"] = String(humid);


    String requestBody;
    serializeJson(doc, requestBody);

    // Setup HTTP client
    HTTPClient http;
    http.begin(POST_API_URL);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(requestBody);
    bool success = (httpResponseCode > 0);

    if (success)
    {
        Serial.printf("Data sent successfully, response code: %d\n", httpResponseCode);
    }
    else
    {
        Serial.printf("Error on HTTP request, code: %d\n", httpResponseCode);
    }

    http.end();

    return success;
}

#endif // SEND_DATA_H
