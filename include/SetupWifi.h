#pragma once
#include <WiFi.h>

extern bool ConnectedToWifi;

// Connects to WiFi using defined SSID and PASSWORD
bool ConnectWiFi();

// Attempts to setup WiFi connection
void TrySetupWifi();