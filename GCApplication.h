#ifndef GEIGERCOUNTER_APPLICATION_H
#define GEIGERCOUNTER_APPLICATION_H

#include <Arduino.h>
#include "Display.h"
#include "GeigerCounter.h"
#include "BluetoothServer.h"
#include "BLEButton.h"
#include "LED.h"

#define BLUETOOTH_BTN_PIN 19
#define TOGGLE_BTN_PIN 23

#define GREEN_LED_PIN 21
#define RED_LED_PIN 22

#define GEIGER_COUNTER_PIN 18

class GCApplication {

public:

    GCApplication();
    ~GCApplication();

    void setup();
    void loop();

private:

    BLEButton* bleButton;
    //LED* greenLED;
    //LED* redLED;

};


#endif
