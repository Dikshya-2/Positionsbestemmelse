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
    Serial.print("MQTT publisher ready on topic: ");
    Serial.println(_topic);
}
