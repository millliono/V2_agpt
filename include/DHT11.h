#ifndef DHT111_H
#define DHT111_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h>

class DHT111
{
public:
    DHT111(uint8_t DHTPIN, String sensorAddress);

    void initialize();
    float getTemperature();
    float getHumidity();
    void debug();
    JsonDocument createJsonDoc(int sensorId, float value);

private:
    uint8_t pin;
    DHT_Unified dht;
    String sensorAddress;
};

#endif // DHT111_H
