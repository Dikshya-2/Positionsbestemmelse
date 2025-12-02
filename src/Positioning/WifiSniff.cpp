#include "Positioning/WifiSniff.h"

void initializeWifiSniffer()
{
  WiFi.mode(WIFI_STA);                                 // Set ESP32 to station mode
  WiFi.disconnect();                                   // Disconnect from any Wi-Fi network
  esp_wifi_set_promiscuous(true);                      // Enable promiscuous mode to sniff packets
  esp_wifi_set_promiscuous_filter(NULL);               // No filter, sniff everything
  esp_wifi_set_promiscuous_rx_cb(promiscuousCallback); // Set the callback function
}

// Callback to handle the sniffed packets
void promiscuousCallback(void *buf, wifi_promiscuous_pkt_type_t type)
{
  wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;

  if (type == WIFI_PKT_MGMT)
  {
    int rssi = pkt->rx_ctrl.rssi;               // Get the RSSI (signal strength)
    String mac = macAddressToStr(pkt->payload); // Get the MAC address
    uint32_t t = micros();                      // receive time on this device
    uint8_t *payload = pkt->payload;
    uint16_t seqCtrl = payload[22] | (payload[23] << 8);

    // Build Json and send it to pipeline
    char *json = CreateNodeJson(mac.c_str(), String(t), rssi, String(seqCtrl));
    if (json != nullptr)
    {
      mqttPub.publish(json); // Publish JSON via MQTT
      free(json);         // Free allocated memory for JSON string
    }

    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.print(" MAC: ");
    Serial.println(mac);
  }
}

// Convert MAC address to a human-readable string
String macAddressToStr(uint8_t *mac)
{
  char str[18];
  sprintf(str, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(str);
}
