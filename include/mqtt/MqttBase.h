#pragma once

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "SetupWifi.h"

class MqttBase
{
public:
    MqttBase();
    MqttBase(const char *server,
             uint16_t port,
             const char *topic,
             const String &user,
             const String &pass);

    // Call from loop()
    void trySetup(bool connectedToWifi, bool timeIsSetup);
    void loop(bool connectedToWifi);
    bool _mqttIsSetup = false;
    bool _connected = false;

protected:
    bool mqtt_setup();
    void mqtt_reconnect();

    // Hook for derived classes (subscribe, etc.)
    virtual void onConnected();

protected:
    WiFiClientSecure espClient;
    PubSubClient mqttClient;

    String _user;
    String _pass;
    const char *_server;
    uint16_t _port;
    const char *_topic;
};
