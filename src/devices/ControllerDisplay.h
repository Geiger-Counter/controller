#ifndef GEIGERCOUNTER_CONTROLLER_DISPLAY_H
#define GEIGERCOUNTER_CONTROLLER_DISPLAY_H

#include <Arduino.h>
#include <heltec.h>
#include "./../MainHandler.h"
#include "./../icons.h"

class ControllerDisplay {

public:

    static void setup();
    static void loop();

    static void updateStatistic(float msv, int cpm);

private:

    static float msv;
    static int cpm;

    static void printBLEIcon();
    static void printBattery();
    static void renderStatistics();

};

#endif