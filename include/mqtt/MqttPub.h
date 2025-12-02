#pragma once

#include "MqttBase.h"

class MqttPub : public MqttBase
{
public:
    using MqttBase::MqttBase;  // inherit constructor

    bool publish(const String& payload);

protected:
    void onConnected() override;  // optional, here just for symmetry
};
