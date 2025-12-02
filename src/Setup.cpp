#include "Setup.h"

TrilaterationManager trilaterationManager(-59.0f, 2.0f);

//192.168.0.161 wilson.local
MqttPub mqttPub = MqttPub("wilson.local", 8883, "esp32/DTJ/pipeline", "elev1", "password");
MqttSub mqttSub = MqttSub("wilson.local", 8883, "esp32/DTJ/node", "node", "password");

void SetupMqtt()
{
    if (!PipeLineMode)
    {
        mqttSub = MqttSub("", 0, "", "", "");
        mqttPub = MqttPub("wilson.local", 8883, "esp32/node", "node", "password");
    }

    mqttPub.trySetup(TimeIsSetup, ConnectedToWifi);
    //mqttSub.trySetup(TimeIsSetup, ConnectedToWifi);
}

void SetupTrilaterationAnchors()
{
    // Example anchor positions (in meters)
    trilaterationManager.SetAnchor(0, 0.0f, 0.0f);  // Anchor 1 at (0,0)
    trilaterationManager.SetAnchor(1, 5.0f, 0.0f);  // Anchor 2 at (5,0)
    trilaterationManager.SetAnchor(2, 2.5f, 4.33f); // Anchor 3 at (2.5,4.33) forming an equilateral triangle
}

void SetUpPipelineMode()
{
    Serial.print("Is this pipeline mode? (Y/N): ");
    while (!Serial.available())
    {
        // wait for input
    }

    char c = Serial.read();
    c = toupper(c); // make case-insensitive

    PipeLineMode = (c == 'Y');

    Serial.println(PipeLineMode ? " Yes" : " No");
}

bool PipeLineMode;