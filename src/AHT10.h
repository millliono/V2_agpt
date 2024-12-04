#ifndef AHT10_H
#define AHT10_H

#include <Adafruit_AHTX0.h>
#include <ArduinoJson.h>
#include <Wire.h>

#include "Common.h"

class AHT10
{
public:
    AHT10(String sensorAddress);

    void initialize();
    float getTemperature();
    float getHumidity();
    void debug();
    JsonDocument createJsonDoc(int sensorId, float value);

private:
    Adafruit_AHTX0 aht;
    String sensorAddress;
};

#endif // AHT10_H
