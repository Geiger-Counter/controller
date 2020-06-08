#ifndef GEIGERCOUNTER_CONTROLLER_DISPLAY_H
#define GEIGERCOUNTER_CONTROLLER_DISPLAY_H

#include <Arduino.h>
#include <heltec.h>
#include "./../MainHandler.h"
#include "./../icons.h"

enum ControllerDisplayState {
    STATISTIC,
    BLE_CODE,
    NEW_CONNECTION
};

class ControllerDisplay {

public:

    static void setup();
    static void loop();

    static void showBLE();
    static void hideBLE();
    static void showWiFi();
    static void hideWiFi();

    static void updateBattery(float percentage);
    static void updateStatistic(float msv, int cpm);
    static void updateBLECode(String code);
    static void updateNewConnection(String connection);
    static void changeState(ControllerDisplayState state);
    static void toggleState();

    static ControllerDisplayState getState();

private:

    static ControllerDisplayState state;
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