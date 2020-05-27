#ifndef WiFiHandler_H
#define WiFiHandler_H

#include <Arduino.h>
#include <WiFi.h>

class WiFiHandler {

public:

    static void setup(char* ssid, char* password, char* backend_url = nullptr, int interval);
    static bool on();
    static void off();
    static bool is_connected();

private:

    static char* ssid;
    static char* password;
    static char* backend_url;
    static bool connected;
    static int interval;

};

#endif
