#include "mqtt/MqttPub.h"

bool MqttPub::publish(const String& payload)
{
    Serial.print("Publishing payload: ");
    Serial.println(payload);

    if (!mqttClient.connected())
    {
        mqtt_reconnect();
    }
    Serial.println("MQTT Connected");

    return mqttClient.publish(_topic, payload.c_str());
}

void MqttPub::onConnected()
{
    _connected = true;
    Serial.print("MQTT publisher ready on topic: ");
    Serial.println(_topic);
}
