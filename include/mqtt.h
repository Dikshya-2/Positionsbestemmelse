#pragma once

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

class MqttManager
{
public:
    // Type for the user-provided message handler
    // topic = MQTT topic as String
    // payload = MQTT payload as String
    typedef void (*MessageCallback)(const String& topic, const String& payload);

    MqttManager(const char* server,
                uint16_t port,
                const char* topic,
                const String& user,
                const String& pass);

    // Call this from your main code when WiFi and time are ready
    void trySetup(bool connectedToWifi, bool timeIsSetup);

    // Call this from loop()
    void loop(bool connectedToWifi);

    // Publish helper
    bool publish(const String& payload);

    // Set message handler callback
    void setMessageCallback(MessageCallback cb);

    // Optionally expose subscribe to another topic if needed
    bool subscribe(const char* topic);

private:
    bool mqtt_setup();
    void mqtt_reconnect();

    // Internal handler for PubSubClient callback
    void handleIncomingMessage(char* topic, uint8_t* payload, unsigned int length);

    // Static callback wrapper required by PubSubClient
    static void mqttCallback(char* topic, uint8_t* payload, unsigned int length);

private:
    WiFiClientSecure espClient;
    PubSubClient mqttClient;

    String _user;
    String _pass;
    const char* _server;
    uint16_t _port;
    const char* _topic;     // default topic (used for publish + subscribe)

    bool _mqttIsSetup = false;

    // User callback
    MessageCallback _userCallback = nullptr;

    // Static pointer to current instance (for the static callback)
    static MqttManager* _instance;
};
