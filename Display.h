#ifndef GEIGERCOUNTER_DISPLAY_H
#define GEIGERCOUNTER_DISPLAY_H

#include <Arduino.h>
#include "heltec.h"
#include "GeigerCounter.h"
#include "icons.h"

enum DisplayState {
    STATISTIC,
    BLE_CODE,
    NEW_CONNECTION
};

class Display {

public:

    static void setup();
    static void loop();

    static void toggleBLE();
    static void toggleWiFi();

    static void updateBattery(float percentage);
    static void updateStatistic(float msv, int cpm);
    static void updateBLECode(String code);
    static void updateNewConnection(String connection);
    static void changeState(DisplayState state);

    static DisplayState getState();

private:

    static DisplayState state;
    static bool ble_active;
    static bool wifi_active;
    static float battery_charge;
    static bool charging;
    static float msv;
    static int cpm;
    static String ble_connection_code;
    static String info_connection;

    static void printBLEIcon();
    static void printWiFiIcon();
    static void printBattery();
    static void renderStatistics();
    static void renderBLECode();
    static void renderNewConnection();

};

#endif