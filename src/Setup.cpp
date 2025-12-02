#include "Setup.h"

TrilaterationManager trilaterationManager(-59.0f, 2.0f);

// 192.168.0.161 wilson.local
MqttPub mqttPub  = MqttPub("192.168.0.161", 8883, "esp32/DTJ/node", "elev1", "password");
MqttSub mqttSub  = MqttSub("192.168.0.161", 8883, "esp32/DTJ/node", "elev1", "password");

void SetupMqtt()
{
        mqttPub.trySetup(ConnectedToWifi, TimeIsSetup);
        mqttSub.trySetup(ConnectedToWifi, TimeIsSetup);


    // if (!PipeLineMode && mqttPub._mqttIsSetup)
    // {
    //     return;
    // }
    // else if (!PipeLineMode)
    // {
    //     mqttPub = MqttPub("192.168.0.161", 8883, "esp32/DTJ/node", "node", "password");
    //     mqttPub.trySetup(ConnectedToWifi, TimeIsSetup);
    // }
    // else if (PipeLineMode && mqttSub._mqttIsSetup && mqttPub._mqttIsSetup)
    // {
    //     return;
    // }
    // else
    // {
    //     mqttPub = MqttPub("192.168.0.161", 8883, "esp32/DTJ/node", "elev1", "password");
    //     mqttSub = MqttSub("192.168.0.161", 8883, "esp32/DTJ/node", "node", "password");

    //     mqttPub.trySetup(ConnectedToWifi, TimeIsSetup);
    //     mqttSub.trySetup(ConnectedToWifi, TimeIsSetup);
    // }
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