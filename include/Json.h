#pragma once
#include <ArduinoJson.h>

// Creates a JSON payload with the button name and timestamp
char *CreateJson(const char *buttonName, String timeStamp);