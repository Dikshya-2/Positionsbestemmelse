#include "Setup.h"

void setup()
{
    // Start Serial for debugging
    Serial.begin(115200);
    delay(1000);

    SetUpPipelineMode();

    // setup wifi and time
    TrySetupWifi();
    TrySetupTime();
    TrySetupMqtt();

    // setup wifi sniffer
    TrySetupWifiSniffer();
}

void loop()
{
    // reconnect to wifi
    TrySetupWifi();

    // reset time
    TrySetupTime();

    // keep mqtt connection alive
    TrySetupMqtt();
    if (PipeLineMode)
    {
        mqttSub->loop(WiFi.status() == WL_CONNECTED);
    }
    mqttPubNode->loop(WiFi.status() == WL_CONNECTED);

    TrySetupWifiSniffer();
}