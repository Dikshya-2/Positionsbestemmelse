#include "mqtt/MqttPub.h"

bool MqttPub::publish(const String& payload)
{
    if (!mqttClient.connected())
    {
        mqtt_reconnect();
    }

    return mqttClient.publish(_topic, payload.c_str());
}

void MqttPub::onConnected()
{
    // Publisher doesn't need to do anything special on connect
    // (but you could log here if you like)
    Serial.print("MQTT publisher ready on topic: ");
    Serial.println(_topic);
}
