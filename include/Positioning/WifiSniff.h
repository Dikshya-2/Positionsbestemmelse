#pragma once

// Function to initialize the Wi-Fi sniffer
void initializeWifiSniffer();

// Callback function to handle the sniffed packets
void promiscuousCallback(void *buf, wifi_promiscuous_pkt_type_t type);

// Function to convert MAC address to string
String macAddressToStr(uint8_t* mac);
