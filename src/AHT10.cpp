#include "AHT10.h"

AHT10::AHT10(String sensorAddress) : sensorAddress(sensorAddress) {}

void AHT10::initialize()
{
    while (!aht.begin())
    {
    }
}

float AHT10::getTemperature()
{
    sensors_event_t humidity, temp;
    if (!aht.getEvent(&humidity, &temp))
    {
        Serial.println(F("Error reading temperature!"));
    }
    else
    {
        return temp.temperature;
    }
    return NAN;
}

float AHT10::getHumidity()
{
    sensors_event_t humidity, temp;
    if (!aht.getEvent(&humidity, &temp))
    {
        Serial.println(F("Error reading humidity!"));
    }
    else
    {
        return temp.relative_humidity;
    }
    return NAN;
}

void AHT10::debug()
{
    Serial.println("Humidity: " + String(getHumidity()));
    Serial.println("Temperature: " + String(getTemperature()));
}

JsonDocument AHT10::createJsonDoc(int sensorId, float value)
{
    return Common::createJsonDoc(sensorAddress, sensorId, value);
}