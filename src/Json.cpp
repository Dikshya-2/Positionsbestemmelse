#include <ArduinoJson.h>
#include "Json.h"

char *CreateNodeJson(const char *id, String timeStamp, int rssi, String payload, String nodeID)
{
    JsonDocument doc;
    doc["NodeID"] = nodeID;
    doc["ID"] = id;
    doc["Time"] = timeStamp;
    doc["RSSI"] = rssi;
    doc["Payload"] = payload;

    static char jsonBuffer[100];
    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
    return jsonBuffer;
}

char *CreatePipelineJson(const char *id, const String timeStamp, float x, float y)
{
    static char jsonBuffer[200];

    JsonDocument doc;
    doc["ID"] = id;
    doc["Time"] = timeStamp;

    // Create "position": [x, y]
    doc["Position"].to<JsonArray>();
    doc["Position"].add(x);
    doc["Position"].add(y);

    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
    return jsonBuffer;
}