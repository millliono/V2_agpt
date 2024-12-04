#ifndef COMMON_H
#define COMMON_H

#include "ArduinoJson.h"

class Common
{
public:
    static JsonDocument createJsonDoc(String sensorAddress, int sensorId, float value);
};

#endif 