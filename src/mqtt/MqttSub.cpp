#include "mqtt/MqttSub.h"

void MqttSub::setCallback(MQTT_CALLBACK_SIGNATURE)
{
    mqttClient.setCallback(callback);
}

void MqttSub::onConnected()
{
    Serial.print("Subscribing to topic: ");
    Serial.println(_topic);

    if (mqttClient.subscribe(_topic))
    {
        _connected = true;
        Serial.println("Subscribed successfully");
    }
    else
    {
        Serial.println("Subscription failed");
    }
}