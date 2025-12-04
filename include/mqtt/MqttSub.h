#pragma once

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <math.h>
#include <queue>
#include "MqttBase.h"
#include "Positioning/Trilateration.h"
#include "Json.h"

// PubSubClient defines MQTT_CALLBACK_SIGNATURE macro for the callback type.

extern TrilaterationManager trilat;

// Last RSSI from each sniffer
extern float g_rssi[3];
extern bool g_rssiValid[3];

extern std::queue<char *> positions;

class MqttSub : public MqttBase
{
public:
    using MqttBase::MqttBase; // inherit constructor

    // Wrap PubSubClient's setCallback
    void setCallback(MQTT_CALLBACK_SIGNATURE);
    static void StaticCallback(char *topic, byte *payload, unsigned int length);

protected:
    void onConnected() override; // subscribe when connected
};