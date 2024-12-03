#include "DHT11.h"

DHT111::DHT111(uint8_t DHTPIN, String sensorAddress) : pin(DHTPIN), sensorAddress(sensorAddress), dht(DHTPIN, DHT11) {}

void DHT111::initialize()
{
    dht.begin();
}

float DHT111::getTemperature()
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);

    if (isnan(event.temperature))
    {
        Serial.println(F("Error reading temperature!"));
    }
    else
    {
        return event.temperature;
    }
    return NAN; // Return NaN in case of error
}

float DHT111::getHumidity()
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);

    if (isnan(event.relative_humidity))
    {
        Serial.println(F("Error reading humidity!"));
    }
    else
    {
        return event.relative_humidity;
    }
    return NAN; // Return NaN in case of error
}

void DHT111::debug()
{
    Serial.println("Humidity: " + String(getHumidity()));
    Serial.println("Temperature: " + String(getTemperature()));
}

JsonDocument DHT111::createJsonDoc(int sensorId, float value)
{
    JsonDocument doc;
    doc["query"] = "mutation CreateEntry($entryInput: EntryCreate!) { createEntry(entryInput: $entryInput) { _id address sensor value }}";
    JsonObject variables_entryInput = doc["variables"]["entryInput"].to<JsonObject>();
    variables_entryInput["address"] = sensorAddress;
    variables_entryInput["sensor"] = sensorId;
    variables_entryInput["value"] = value;
    return doc;
}
