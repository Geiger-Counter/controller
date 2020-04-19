#include "Display.h"

DisplayState Display::state = STATISTIC;
bool Display::ble_active = false;
bool Display::wifi_active = false;
float Display::battery_charge = 100.0;
bool Display::charging = false;
float Display::msv = 0.0;
int Display::cpm = 0;
String Display::ble_connection_code = "";
String Display::info_connection = "";

void Display::setup()
{
    Heltec.begin(true, false, true);
    randomSeed(analogRead(0));
}

void Display::loop() 
{

    Heltec.display->clear();
    Heltec.display->setFont(ArialMT_Plain_10);
    
    if(ble_active) {
        printBLEIcon();
    }

    if(wifi_active) {
        printWiFiIcon();
    }

    printBattery();

    switch(state) {
        case STATISTIC:
            renderStatistics();
            break;
        case BLE_CODE:
            renderBLECode();
            break;
        case NEW_CONNECTION:
            renderNewConnection();
            break;
        default:
            break;        
    }

    Heltec.display->display();

}

void Display::toggleBLE() 
{
    ble_active = !ble_active;
}

void Display::toggleWiFi()
{
    wifi_active = !wifi_active;
}

void Display::updateBattery(float percentage)
{
    battery_charge = percentage;
}

void Display::updateStatistic(float _msv, int _cpm)
{
    msv = _msv;
    cpm = _cpm;
}

void Display::updateBLECode(String code)
{
    ble_connection_code = code;
}

void Display::updateNewConnection(String connection)
{
    info_connection = connection;
}

void Display::changeState(DisplayState _state) {
    state = _state;
}

void Display::printBLEIcon() 
{
    Heltec.display->drawXbm(2, 2, ble_icon_width, ble_icon_height, ble_icon_bits);
}

void Display::printWiFiIcon() 
{
    int width = ble_active ? 13 : 2;
    Heltec.display->drawXbm(width, 2, wifi_icon_width, wifi_icon_height, wifi_icon_bits);
}

void Display::printBattery()
{
    Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
    Heltec.display->drawString(126, 2, String(battery_charge, 0) + "%");
}

void Display::renderStatistics()
{
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->drawString(2, 24, "mSv/h:    " + String(msv));
    Heltec.display->drawString(2, 44, "CPM:      " + String(cpm));
}

void Display::renderBLECode()
{
    Heltec.display->setFont(ArialMT_Plain_24);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
    Heltec.display->drawString(32, 64, ble_connection_code);
}

void Display::renderNewConnection()
{
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
    Heltec.display->drawString(32, 64, "Connected to: " + info_connection);
}