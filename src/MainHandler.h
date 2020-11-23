#ifndef GEIGERCOUNTER_MAIN_HANDLER_H
#define GEIGERCOUNTER_MAIN_HANDLER_H

#include <Arduino.h>
#include <SPI.h>
#include "./ble/BluetoothServer.h"
#include "LinkedList.h"
#include "./devices/ControllerDisplay.h"
#include "./devices/ControllerRGBLED.h"
#include "./devices/ControllerLED.h"
#include "Calculator.h"

#define GC_LOG_PERIOD 5000
#define GC_LOG_SIZE 500

#define ON_OFF_LED_PIN 13
#define RED_LED_PIN 12
#define BLUE_LED_PIN 14
#define GREEN_LED_PIN 27

enum ButtonState {
    START,
    STOP,
    WAIT,
    RUNNING
};

class MainHandler {

public:

    static void setup(int GEIGER_PIN, BluetoothServer* server);
    static float get_microsievert();
    static int get_counts_per_minute();
    static void loop();
    static void impulse();
    static void start_bluetooth();
    static void stop_bluetooth();
    static void toggle_bluetooth();

private:

    static int cpm;
    static unsigned long previous_ms;
    static LinkedList<long> detections;
    static ButtonState bleState;
    static BluetoothServer* bluetoothServer;
    static ControllerLED* statusLED;
    static ControllerRGBLED* rgbLED;

};

#endif