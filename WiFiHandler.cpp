#include "WiFiHandler.h"

char* WiFiHandler::ssid = nullptr;
char* WiFiHandler::password = nullptr;
char* WiFiHandler::backend_url = nullptr;
bool WiFiHandler::connected = false;
int WiFiHandler::interval = 3600;

void WiFiHandler::setup(char* ssid, char* password, char* backend_url, int interval) {

    ssid = ssid;
    password = password;
    backend_url = backend_url;
    interval = interval;

}

bool WiFiHandler::on() {
    int status = WiFi.begin(ssid, password);
    if(status != WL_CONNECTED) {
        Serial.println("Couldn't get a wifi connection");
        return false;
    } else {
        Serial.println("Connected");
        connected = true;
        return true;
    }
}

void WiFiHandler::off() {
    WiFi.disconnect();
    connected = false;
}

bool WiFiHandler::is_connected() {
    return connected;
}