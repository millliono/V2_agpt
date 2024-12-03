#ifndef APICLIENT_H
#define APICLIENT_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

class ApiClient
{
public:
    ApiClient(const String hostUrl);

    void sendJson(JsonDocument doc);

private:
    String host;
    HTTPClient http;
};

#endif // APICLIENT_H
