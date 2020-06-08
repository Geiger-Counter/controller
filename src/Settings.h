#ifndef GEIGERCOUNTER_SETTINGS_H
#define GEIGERCOUNTER_SETTINGS_H

#include <Arduino.h>
#include "./wifi/API.h"
#include "StaticMemory.h"

struct APISettings {
    const char* endpoint_uri;
    const char* username;
    const char* token;
};

struct Settings {
    const char* ssid;
    const char* password;
    bool auditive_counter;
    struct APISettings* api;
};

struct Settings* load_settings();
bool save_settings(struct Settings* settings);

#endif
