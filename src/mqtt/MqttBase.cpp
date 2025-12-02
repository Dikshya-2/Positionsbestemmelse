#include "mqtt/MqttBase.h"

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
        _mqttIsSetup = mqtt_setup();
    }
}

bool MqttBase::mqtt_setup()
{
    // Configure MQTT over TLS
    espClient.setInsecure();
    mqttClient.setServer(_server, _port);
    return true;
}

void MqttBase::loop(bool connectedToWifi)
{
    if (!connectedToWifi)
    {
        return;
    }

    if (!mqttClient.connected())
    {
        mqtt_reconnect();
    }

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
