#ifndef GEIGERCOUNTER_MAIN_APPLICATION_H
#define GEIGERCOUNTER_MAIN_APPLICATION_H

#include <Arduino.h>
#include "./devices/ControllerDisplay.h"
#include "MainHandler.h"
#include "./ble/BluetoothServer.h"
#include "./devices/ControllerButton.h"
#include "./devices/ControllerLED.h"
#include "./devices/ControllerRGBLED.h"

/**
 * 
 * 
 * 
*/
class GeigerCounter {

public:

    GeigerCounter();
    ~GeigerCounter();

    void setup(int IMP_PIN, int BLE_BTN_PIN, int SGN_BTN_PIN, int SNG_PIN, int R_PIN, int B_PIN, int G_PIN);
    void loop();

    static void execute_isr(int index);

private:

    ControllerButton* bleButton;
    ControllerButton* signalButton;

    static volatile int isr[3];
    static void check_isr();
    

};


#endif
