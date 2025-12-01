#include "SetupWifi.h"
#include "esp_sntp.h"

const char *ssid = "TEC-IOT";
const char *password = "42090793";
bool ConnectedToWifi = false;

bool ConnectWiFi()
{
    // Start connecting
    Serial.print("Connecting to WiFi SSID: ");
    Serial.println(ssid);

    // Begin WiFi connection
    WiFi.begin(ssid, password);

    // Enable SNTP server mode via DHCP
    esp_sntp_servermode_dhcp(1);

    // Try to connect 30 times
    int maxAttempts = 30;
    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    // Check if connected
    if (WiFi.status() == WL_CONNECTED)
    {
        // Output wifi data
        Serial.println("WiFi connected!");
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        return true;
    }
    else
    {
        // Failed to connect
        Serial.println("Failed to connect to WiFi.");
        return false;
    }
}

void TrySetupWifi()
{
    // Setup Wifi
    if (!ConnectedToWifi)
    {
        ConnectedToWifi = ConnectWiFi();
    }
}