#include <ArduinoJson.h>
#include "Json.h"

char *CreateJson(const char *buttonName, String timeStamp)
{
    JsonDocument doc;
    doc["Button"] = buttonName;
    doc["Time"] = timeStamp;

    static char jsonBuffer[100];
    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
    return jsonBuffer;
}
