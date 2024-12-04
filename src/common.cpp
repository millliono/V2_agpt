#include "Common.h"

JsonDocument Common::createJsonDoc(String sensorAddress, int sensorId, float value)
{
    JsonDocument doc;
    doc["query"] = "mutation CreateEntry($entryInput: EntryCreate!) { createEntry(entryInput: $entryInput) { _id address sensor value }}";
    JsonObject variables_entryInput = doc["variables"]["entryInput"].to<JsonObject>();
    variables_entryInput["address"] = sensorAddress;
    variables_entryInput["sensor"] = sensorId;
    variables_entryInput["value"] = value;
    return doc;
}