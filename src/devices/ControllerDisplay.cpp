#include "ControllerDisplay.h"

ControllerDisplayState ControllerDisplay::state = STATISTIC;
bool ControllerDisplay::ble_active = false;
bool ControllerDisplay::wifi_active = false;
float ControllerDisplay::battery_charge = 100.0;
bool ControllerDisplay::charging = false;
float ControllerDisplay::msv = 0.0;
int ControllerDisplay::cpm = 0;
String ControllerDisplay::ble_connection_code = "";
String ControllerDisplay::info_connection = "";

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

void ControllerDisplay::showBLE() {
    ble_active = true;
}

void ControllerDisplay::hideBLE() {
    ble_active = false;
}

void ControllerDisplay::showWiFi(){
    wifi_active = true;
}

void ControllerDisplay::hideWiFi() {
    wifi_active = false;
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

void ControllerDisplay::updateBLECode(String code)
{
    ble_connection_code = code;
}

void ControllerDisplay::updateNewConnection(String connection)
{
    info_connection = connection;
}

void ControllerDisplay::changeState(ControllerDisplayState _state) {
    state = _state;
}

void ControllerDisplay::toggleState() {
    
}

void ControllerDisplay::printBLEIcon() 
{
    Heltec.display->drawXbm(2, 2, BT_width, BT_height, BT_bits);
}

void ControllerDisplay::printWiFiIcon() 
{
    int width = ble_active ? 12 : 2;
    Heltec.display->drawXbm(width, 2, WIFI_width, WIFI_height, WIFI_bits);
}

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

void ControllerDisplay::renderBLECode()
{
    Heltec.display->setFont(ArialMT_Plain_24);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
    Heltec.display->drawString(32, 64, ble_connection_code);
}

void ControllerDisplay::renderNewConnection()
{
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
    Heltec.display->drawString(32, 64, "Connected to: " + info_connection);
}