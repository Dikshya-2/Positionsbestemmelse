#pragma once
#ifndef SETUP_H
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Json.h"
#include "Positioning/Trilateration.h"
#include "SetupWifi.h"
#include "SetupTime.h"
#include "mqtt/MqttPub.h"
#include "mqtt/MqttSub.h"
#include "Positioning/WifiSniff.h"

extern TrilaterationManager trilaterationManager;
extern MqttPub *mqttPubNode;
extern MqttPub *mqttPubPipe;
extern MqttSub *mqttSub;

void SetupTrilaterationAnchors();
void SetUpPipelineMode();
void TrySetupMqtt();
void KeepMqttAlive();

extern bool PipeLineMode;

#endif