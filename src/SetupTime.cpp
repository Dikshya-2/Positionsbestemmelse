#include "SetupTime.h"

bool TimeIsSetup = false;

// NTP server
const char *ntpServer = "pool.ntp.org";

// Timezone string for Central European Time (CET) with Daylight Saving Time (CEST)
const char *timezone = "CET-1CEST,M3.5.0/2,M10.5.0/3";

bool SetupTime()
{
    // Configure NTP
    configTime(0, 0, ntpServer);

    // Wait for time to be set
    Serial.println("Waiting for NTP time…");
    struct tm timeinfo;

    // Wait until we get the time
    while (!getLocalTime(&timeinfo))
    {
        // Still waiting
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nGot NTP time (UTC)");

    // Set timezone
    setenv("TZ", timezone, 1);
    tzset();

    // Confirm time is set
    return true;
}

String GetLocalTime()
{
    // Get local time
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        // Failed to obtain time
        Serial.println("Failed to obtain time");
        char *val = "Failed to obtain time";
        return val;
    }

    // Format time as string
    return getFormattedTime(timeinfo);
}

String getFormattedTime(const struct tm &timeinfo)
{
    // Format: YYYY-MM-DD HH:MM:SS
    char buffer[25];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(buffer);
}

void TrySetupTime()
{
    // Setup time if WiFi is connected and time not yet set up
    if (WiFi.status() == WL_CONNECTED && !TimeIsSetup)
    {
        TimeIsSetup = SetupTime();
    }
}