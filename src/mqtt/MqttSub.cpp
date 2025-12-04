#include "mqtt/MqttSub.h"

TrilaterationManager trilat(-59.0f, 2.0f);
// Last RSSI from each sniffer
float g_rssi[3] = {NAN, NAN, NAN};
bool g_rssiValid[3] = {false, false, false};

std::queue<char *> positions;


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
    // Debug: print raw payload
    Serial.print("Got message on topic [");
    Serial.print(topic);
    Serial.print("]: ");
    for (unsigned int i = 0; i < length; i++)
        Serial.print((char)payload[i]);
    Serial.println();

    // Parse JSON from payload
    JsonDocument inDoc;
    DeserializationError err = deserializeJson(inDoc, payload, length);

    if (err)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(err.f_str());
        return;
    }

    // ---- Get NodeID from payload ----
    int anchorIndex = -1;

    // Handle NodeID as int or string
    if (inDoc["NodeID"].is<int>())
    {
        anchorIndex = inDoc["NodeID"].as<int>();
    }
    else if (inDoc["NodeID"].is<const char*>())
    {
        const char *nodeIdStr = inDoc["NodeID"];
        anchorIndex = atoi(nodeIdStr);   // "0" -> 0, "1" -> 1, etc.
    }

    if (anchorIndex < 0 || anchorIndex > 2)
    {
        Serial.print("Invalid NodeID: ");
        Serial.println(anchorIndex);
        return;
    }

    // ---- Read the rest of the fields ----
    const char *id   = inDoc["ID"]   | "";
    const char *time = inDoc["Time"] | "";
    float rssi       = inDoc["RSSI"] | NAN;

    if (isnan(rssi))
    {
        Serial.println("RSSI missing or invalid");
        return;
    }

    // Store RSSI for this anchor
    g_rssi[anchorIndex]      = rssi;
    g_rssiValid[anchorIndex] = true;

    Serial.print("Anchor ");
    Serial.print(anchorIndex);
    Serial.print(" RSSI = ");
    Serial.println(rssi);

    // Check if we have all three RSSIs
    bool haveAll = g_rssiValid[0] && g_rssiValid[1] && g_rssiValid[2];
    if (!haveAll)
        return;

    // ---- Trilateration ----
    Vec2 pos = trilat.estimatePosition(g_rssi[0], g_rssi[1], g_rssi[2]);

    if (isnan(pos.x) || isnan(pos.y))
    {
        Serial.println("Trilateration failed (degenerate geometry / bad data).");
        return;
    }

    // ---- Build output JSON ----
    char *outJson = CreatePipelineJson(id, String(time), pos.x, pos.y);

    Serial.print("Pipeline JSON: ");
    Serial.println(outJson);

    positions.push(outJson);
}