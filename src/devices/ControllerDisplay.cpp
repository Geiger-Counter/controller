#include "ControllerDisplay.h"

bool ControllerDisplay::ble_active = false;
float ControllerDisplay::battery_charge = 100.0;
bool ControllerDisplay::charging = false;
float ControllerDisplay::msv = 0.0;
int ControllerDisplay::cpm = 0;

void ControllerDisplay::setup()
{
    Heltec.begin(true, false, true);
    randomSeed(analogRead(0));
}

void ControllerDisplay::loop() 
{

    Heltec.display->clear();
    Heltec.display->setFont(ArialMT_Plain_10);
    

    if(ble_active) {
        printBLEIcon();
    }

    printBattery();
    renderStatistics();

    Heltec.display->display();

}

void ControllerDisplay::showBLE() {
    ble_active = true;
}

void ControllerDisplay::hideBLE() {
    ble_active = false;
}

void ControllerDisplay::updateBattery(float percentage)
{
    battery_charge = percentage;
}

void ControllerDisplay::updateStatistic(float _msv, int _cpm)
{
    msv = _msv;
    cpm = _cpm;
}

void ControllerDisplay::printBLEIcon() 
{
    Heltec.display->drawXbm(2, 2, BT_width, BT_height, BT_bits);
}

/** 
void ControllerDisplay::printWiFiIcon() 
{
    int width = ble_active ? 12 : 2;
    Heltec.display->drawXbm(width, 2, WIFI_width, WIFI_height, WIFI_bits);
}*/

void ControllerDisplay::printBattery()
{
    Heltec.display->drawXbm(106, 2, BAT_width, BAT_height, BAT_bits);
}

void ControllerDisplay::renderStatistics()
{
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->drawString(2, 24, "µSv/h:    " + String(MainHandler::get_microsievert()));
    Heltec.display->drawString(2, 44, "CPM:      " + String(MainHandler::get_counts_per_minute()));
}