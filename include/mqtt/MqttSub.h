#pragma once

#include "MqttBase.h"
#include <PubSubClient.h>

// PubSubClient defines MQTT_CALLBACK_SIGNATURE macro for the callback type.

class MqttSub : public MqttBase
{
public:
    using MqttBase::MqttBase;  // inherit constructor

    // Wrap PubSubClient's setCallback
    void setCallback(MQTT_CALLBACK_SIGNATURE);

protected:
    void onConnected() override;  // subscribe when connected
};
