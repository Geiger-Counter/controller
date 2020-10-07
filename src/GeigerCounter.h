#ifndef GEIGERCOUNTER_MAIN_APPLICATION_H
#define GEIGERCOUNTER_MAIN_APPLICATION_H

#include <Arduino.h>
#include "Settings.h"
#include "./devices/ControllerDisplay.h"
#include "MainHandler.h"
#include "./ble/BluetoothServer.h"
#include "./devices/ControllerButton.h"
#include "./devices/ControllerLED.h"

#define BLUETOOTH_BTN_PIN 19
#define WIFI_BTN_PIN 5
#define TOGGLE_BTN_PIN 23

#define GREEN_LED_PIN 21
#define RED_LED_PIN 22

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
    ControllerButton* toggleButton;
    
    ControllerLED* greenLED;
    ControllerLED* redLED;
    ControllerLED* statusLED;

    static volatile int isr[3];
    static void check_isr();
    

};


#endif
