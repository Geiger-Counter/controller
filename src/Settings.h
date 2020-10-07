#ifndef GEIGERCOUNTER_SETTINGS_H
#define GEIGERCOUNTER_SETTINGS_H

#include <Arduino.h>
#include "./wifi/API.h"
#include "StaticMemory.h"

class APISettings {
    public: 
        const char* endpoint_uri;
        const char* username;
        const char* token;
};

class Settings {
    public: 
        const char* ssid;
        const char* password;
        APISettings* api;
};

Settings* load_settings();
bool save_settings(Settings* settings);

#endif
