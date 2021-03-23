#include "ControllerDisplay.h"

float ControllerDisplay::msv = 0.0;
int ControllerDisplay::cpm = 0;

void ControllerDisplay::setup()
{
    Heltec.begin(true, false, true);
}

void ControllerDisplay::loop() 
{

    Heltec.display->clear();
    Heltec.display->setFont(ArialMT_Plain_10);
    

    printBLEIcon();
    printBattery();
    renderStatistics();

    Heltec.display->display();

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