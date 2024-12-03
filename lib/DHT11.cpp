#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h>

class DHT111
{
public:
    DHT111(uint8_t DHTPIN, String sensorAddress) : pin(DHTPIN), sensorAddress(sensorAddress), dht(DHTPIN, DHT11) {}

    void initialize()
    {
        dht.begin();
    }

    float getTemperature()
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
    }

    float getHumidity()
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
    }

    void debug()
    {
        Serial.println("Humidity: " + String(getHumidity()));
        Serial.println("Temperature: " + String(getTemperature()));
    }

    // Create JSON payload
    JsonDocument createJsonDoc(int sensorId, float value)
    {
        JsonDocument doc;
        doc["query"] = "mutation CreateEntry($entryInput: EntryCreate!) { createEntry(entryInput: $entryInput) { _id address sensor value }}";
        JsonObject variables_entryInput = doc["variables"]["entryInput"].to<JsonObject>();
        variables_entryInput["address"] = sensorAddress;
        variables_entryInput["sensor"] = sensorId;
        variables_entryInput["value"] = value;
        return doc;
    }

private:
    uint8_t pin;
    DHT_Unified dht;
    String sensorAddress;
};
