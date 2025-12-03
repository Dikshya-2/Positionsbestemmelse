#pragma once
#include <string>
#include <WiFi.h>
#include <esp_wifi.h>
#include "Json.h"
#include "Setup.h"

extern bool WifiSnifferInitialized;
// Function to initialize the Wi-Fi sniffer
void initializeWifiSniffer();

// Callback function to handle the sniffed packets
static void promiscuousCallback(void *buf, wifi_promiscuous_pkt_type_t type);

// Function to convert MAC address to string
String macAddressToStr(uint8_t* mac);

void TrySetupWifiSniffer();
