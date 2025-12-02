#include "mqtt/MqttBase.h"

MqttBase::MqttBase()
    : espClient(),
      mqttClient(espClient),
      _server(nullptr),
      _port(0),
      _topic(nullptr),
      _user(""),
      _pass("")
{
    _mqttIsSetup = false;
}

MqttBase::MqttBase(const char *server,
                   uint16_t port,
                   const char *topic,
                   const String &user,
                   const String &pass)
    : mqttClient(espClient),
      _user(user),
      _pass(pass),
      _server(server),
      _port(port),
      _topic(topic)
{
}

void MqttBase::trySetup(bool connectedToWifi, bool timeIsSetup)
{
    if (connectedToWifi && timeIsSetup && !_mqttIsSetup)
    {
        if (mqtt_setup())
        {
            _mqttIsSetup = true;
            Serial.println("MQTT setup successful");
        }
        else
        {
            _mqttIsSetup = false;
            Serial.println("MQTT setup failed");
        }
    }
}

bool MqttBase::mqtt_setup()
{
    // Configure MQTT over TLS
    Serial.println("MQTT over TLS setup initializing...");
    espClient.setInsecure();
    mqttClient.setServer(_server, _port);
    Serial.println("MQTT over TLS setup completed on Server: " + String(_server) + " Port: " + String(_port));
    return true;
}

void MqttBase::loop(bool connectedToWifi)
{
    Serial.println("MQTT loop running");
    if (!connectedToWifi || mqttClient.state() != -1)
    {
        Serial.println("MQTT loop aborted: not connected to WiFi");
        return;
    }

    Serial.println("MQTT client connected, running loop...");
    Serial.println("MQTT client state: " + String(mqttClient.state()));
    Serial.println("Checking MQTT client connection status...");
    if (!mqttClient.connected())
    {
        Serial.println("MQTT client not connected, attempting to reconnect...");
        delay(50);
            
        mqtt_reconnect();
    }
    Serial.println("MQTT client connected, running loop...");
    mqttClient.loop();
}

void MqttBase::mqtt_reconnect()
{
    while (!mqttClient.connected())
    {
        Serial.print("Connecting to MQTT over TLS...");

        String clientId = "ESP32-" + String(random(0xffff), HEX);

        if (mqttClient.connect(clientId.c_str(), _user.c_str(), _pass.c_str()))
        {
            Serial.println("connected");
            Serial.println("MQTT client state 2: " + String(mqttClient.state()));

            // Let derived classes run their setup (e.g. subscribe)
            onConnected();
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" - retrying in 5 seconds");
            delay(5000);
        }
    }
}

void MqttBase::onConnected()
{
    // Abstract
}
