#pragma once
#ifndef SETUP_H
#include <Arduino.h>
#include <WiFi.h>
#include <OneButton.h>
#include <PubSubClient.h>
#include "Json.h"
#include "SetupTime.h"
#include "PowerSave.h"
#include "mqtt.h"

// LEDs
const int LED_RED = 5;
const int LED_BLUE = 19;
const int LED_GREEN = 21;
const int LED_YELLOW = 23;
const int LED_BUILT_IN = 2;

// Buttons
const int BUTTON_RED = 35;
const int BUTTON_BLUE = 34;
const int BUTTON_GREEN = 32;
const int BUTTON_YELLOW = 33;

// Create  a globalOneButton objects
extern OneButton buttonRed;
extern OneButton buttonBlue;
extern OneButton buttonGreen;
extern OneButton buttonYellow;

// LED management
extern unsigned long ledTimers[4];
extern bool ledActives[4];
const unsigned long LED_ON_TIME = 7000;

// Last activity timestamp
extern unsigned long lastActivity;

// Function to setup pin modes
void PinModeSetup();
#endif