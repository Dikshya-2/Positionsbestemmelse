#include <ArduinoJson.h>
#include "Json.h"

char *CreateNodeJson(const char *id, String timeStamp, int rssi, String payload)
{
    JsonDocument doc;
    doc["ID"] = id;
    doc["Time"] = timeStamp;
    doc["RSSI"] = rssi;
    doc["Payload"] = payload;

    static char jsonBuffer[100];
    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
    return jsonBuffer;
}

char *CreatePipelineJson(const char *id, String timeStamp, float x, float y)
{
    static char jsonBuffer[200];  // increased size for safety

    StaticJsonDocument<200> doc;
    doc["ID"] = id;
    doc["Time"] = timeStamp;

    JsonArray coords = doc["Coordinates"].to<JsonArray>();
    coords.add(x);
    coords.add(y);

    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
    return jsonBuffer;
}

