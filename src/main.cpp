#include "Setup.h"

void setup()
{
    // Start Serial for debugging
    Serial.begin(115200);
    delay(1000);

    // setup wifi and time
    TrySetupWifi();
    TrySetupTime();
    TrySetupMQTT();
}

void loop()
{
    // reconnect to wifi
    TrySetupWifi();

    // reset time
    TrySetupTime();

    // keep mqtt connection alive
    TrySetupMQTT();
    mqtt_loop();
}
