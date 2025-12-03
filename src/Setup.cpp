#include "Setup.h"

TrilaterationManager trilaterationManager(-59.0f, 2.0f);

// 192.168.0.161 wilson.local

MqttPub *mqttPubNode = nullptr;
MqttPub *mqttPubPipe = nullptr;
MqttSub *mqttSub = nullptr;

void SetupMqtt()
{
    if (PipeLineMode)
    {
        if (!mqttPubPipe) {
            mqttPubPipe = new MqttPub("192.168.0.161", 8883, "esp32/DTJ/data", "elev1", "password");
        }
        if (!mqttPubPipe->_mqttIsSetup)
        {
            mqttPubPipe->trySetup(ConnectedToWifi, TimeIsSetup);
        }

        if (!mqttSub) {
            mqttSub = new MqttSub("192.168.0.161", 8883, "esp32/DTJ/node", "elev1", "password");
        }
        if (!mqttSub->_mqttIsSetup)
        {
            mqttSub->trySetup(ConnectedToWifi, TimeIsSetup);
            mqttSub->setCallback(MqttSub::StaticCallback);
        }
    }

    if (!mqttPubNode) {
        mqttPubNode = new MqttPub("192.168.0.161", 8883, "esp32/DTJ/node", "elev1", "password");
    }
    if (!mqttPubNode->_mqttIsSetup)
    {
        mqttPubNode->trySetup(ConnectedToWifi, TimeIsSetup);
    }
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