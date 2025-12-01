#pragma once
#include "time.h"
#include <arduino.h>
#include "SetupWifi.h"

// Indicates if the time has been successfully set up
extern bool TimeIsSetup;

// Sets up the time using NTP
bool SetupTime();

// Retrieves the local time as a formatted string
String GetLocalTime();

// Attempts to set up time synchronization
void TrySetupTime();

// Formats the given time structure into a human-readable string
String getFormattedTime(const struct tm &timeinfo);