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

    // stup mqtt
    SetupMqtt();

    // setup wifi sniffer
    // initializeWifiSniffer();
    // TrySetupWifiSniffer();
}

void loop()
{
    // reconnect to wifi
    TrySetupWifi();

    // reset time
    TrySetupTime();

    // keep mqtt connection alive
    SetupMqtt();
    if (PipeLineMode)
    {
        mqttSub.loop(ConnectedToWifi);
    }
    mqttPub.loop(ConnectedToWifi);

    // TrySetupWifiSniffer();
}
