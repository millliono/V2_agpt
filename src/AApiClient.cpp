#include "ApiClient.h"

ApiClient::ApiClient(const String hostUrl) : host(hostUrl) {}

void ApiClient::sendJson(JsonDocument doc)
{
    if (!http.begin(host))
    {
        Serial.println("Connection error");
        return;
    }

    String jsonPayload;
    serializeJson(doc, jsonPayload);
    Serial.println("Sending payload:");
    Serial.println(jsonPayload);

    // Send POST request
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonPayload);
    if (httpResponseCode == 200)
    {
        String response = http.getString();
        Serial.println("Response:");
        Serial.println(response);
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
