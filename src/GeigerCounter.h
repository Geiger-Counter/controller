#ifndef GEIGERCOUNTER_MAIN_APPLICATION_H
#define GEIGERCOUNTER_MAIN_APPLICATION_H

#include <Arduino.h>
#include "./devices/ControllerDisplay.h"
#include "MainHandler.h"
#include "./ble/BluetoothServer.h"
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

    void setup(int IMP_PIN, int SNG_PIN, int R_PIN, int G_PIN, int B_PIN);
    void loop();
    
};


#endif
