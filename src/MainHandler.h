#ifndef GEIGERCOUNTER_MAIN_HANDLER_H
#define GEIGERCOUNTER_MAIN_HANDLER_H

#include <Arduino.h>
#include <SPI.h>
#include "./ble/BluetoothServer.h"
#include "LinkedList.h"
#include "./wifi/WiFiHandler.h"
#include "./wifi/API.h"
#include "Settings.h"
#include "./devices/ControllerDisplay.h"

#define GC_LOG_PERIOD 5000
#define GC_LOG_SIZE 500

enum ButtonState {
    START,
    STOP,
    WAIT,
    RUNNING
};

class MainHandler {

public:

    static void setup(int GEIGER_PIN, struct Settings* settings, BluetoothServer* server, WiFiHandler* handler);
    static float get_microsievert();
    static unsigned int get_counts_per_minute();
    static void loop();
    static void impulse();
    static void start_bluetooth();
    static void stop_bluetooth();
    static void toggle_bluetooth();
    static void start_wifi();
    static void stop_wifi();
    static void toggle_wifi();
    static struct Settings* get_settings();

private:

    static unsigned int cpm;
    static unsigned long previous_ms;
    static LinkedList<long> detections;
    static ButtonState bleState;
    static ButtonState wifiState;
    static BluetoothServer* bluetoothServer;
    static WiFiHandler* wifiHandler;
    static struct Settings* settings;

    static float get_multiplier();


};

#endif