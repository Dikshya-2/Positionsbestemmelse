#pragma once
#ifndef SETUP_H
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Json.h"
#include "mqtt.h"
#include "Positioning/Trilateration.h"

extern TrilaterationManager trilaterationManager;
void SetupTrilaterationAnchors();

extern bool PipeLineMode;

#endif