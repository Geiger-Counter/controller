#ifndef GEIGERCOUNTER_CONTROLLER_RGB_LED_H
#define GEIGERCOUNTER_CONTROLLER_RGB_LED_H

#include <Arduino.h>

class ControllerRGBLED {

public:

    ControllerRGBLED(int R_PIN, int G_PIN, int B_PIN);
    ~ControllerRGBLED();

    void on(bool r, bool g, bool b);
    void off();
    bool is_on();

private:

    int r_pin;
    int g_pin;
    int b_pin;
    bool active;

};

#endif