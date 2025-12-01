#pragma once
#ifndef SETUP_H
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Json.h"
#include "mqtt.h"
#include "Positioning/Trilateration.h"


TrilaterationManager trilaterationManager(-59.0f, 2.0f);
void SetupTrilaterationAnchors();

#endif