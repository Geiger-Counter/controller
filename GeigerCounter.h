#ifndef GeigerCounter_H
#define GeigerCounter_H

#include <Arduino.h>
#include <SPI.h>
#include "BluetoothServer.h"
#include "Display.h"
#include "LinkedList.h"
#include "WiFiHandler.h"
#include "API.h"
#include "Settings.h"

#define GC_LOG_PERIOD 5000
#define GC_LOG_SIZE 500

enum ButtonState {
    START,
    STOP,
    WAIT,
    RUNNING
};

class GeigerCounter {

public:

    static void setup(int GEIGER_PIN, BluetoothServer* server);
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