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

void MqttSub::StaticCallback(char *topic, byte *payload, unsigned int length)
{
    // Payload is NOT null-terminated, so build a String
    String message;
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    Serial.print("Got message on topic [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.println(message);
}