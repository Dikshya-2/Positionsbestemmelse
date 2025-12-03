#pragma once
#include <WiFi.h>
#include "esp_sntp.h"
#include "SetupTime.h"

// Connects to WiFi using defined SSID and PASSWORD
bool ConnectWiFi();

// Attempts to setup WiFi connection
void TrySetupWifi();