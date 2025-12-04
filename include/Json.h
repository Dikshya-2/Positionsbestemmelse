#pragma once
#include <ArduinoJson.h>

// Creates a JSON payload with the button name and timestamp
char *CreateNodeJson(const char *id, String timeStamp, int rssi, String payload, String nodeID);
char *CreatePipelineJson(const char *id, String timeStamp, float x, float y);
