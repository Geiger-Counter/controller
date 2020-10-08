#ifndef GEIGERCOUNTER_MAIN_APPLICATION_H
#define GEIGERCOUNTER_MAIN_APPLICATION_H

#include <Arduino.h>
#include "Settings.h"
#include "./devices/ControllerDisplay.h"
#include "MainHandler.h"
#include "./ble/BluetoothServer.h"
#include "./devices/ControllerButton.h"
#include "./devices/ControllerLED.h"
#include "./devices/ControllerRGBLED.h"

#define BLUETOOTH_BTN_PIN 19
#define WIFI_BTN_PIN 23

#define GEIGER_COUNTER_PIN 18

/**
 * 
 * 
 * 
*/
class GeigerCounter {

public:

    GeigerCounter();
    ~GeigerCounter();

    void setup();
    void loop();

    static void execute_isr(int index);

private:

    ControllerButton* bleButton;
    ControllerButton* wifiButton;

    static volatile int isr[3];
    static void check_isr();
    

};


#endif
