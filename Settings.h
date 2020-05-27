#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <Arduino.h>
#include "API.h"
#include "StaticMemory.h"

struct APISettings {
    char* endpoint_uri;
    char* username;
    char* token;
} APISettings;

struct Settings {
    char* ssid;
    char* password;
    bool auditive_counter;
    struct APISettings* api;
} Settings;

struct Settings* load_settings();
bool save_settings(struct Settings* settings);

#endif
