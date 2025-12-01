#pragma once
#ifndef SETUP_H
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Json.h"
#include "mqtt.h"

// Function to setup pin modes
void PinModeSetup();
#endif