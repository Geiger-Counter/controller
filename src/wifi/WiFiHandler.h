#ifndef GEIGERCOUNTER_WIFI_HANDLER_H
#define GEIGERCOUNTER_WIFI_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>

class WiFiHandler {

public:

    static void setup(const char* ssid, const char* password, const char* backend_url, int interval);
    static bool on();
    static void off();
    static bool is_connected();

private:

    static const char* ssid;
    static const char* password;
    static const char* backend_url;
    static bool connected;
    static int interval;

};

#endif
