#ifndef GEIGERCOUNTER_CONTROLLER_LED_H
#define GEIGERCOUNTER_CONTROLLER_LED_H

#include <Arduino.h>

class ControllerLED {

public:

    ControllerLED(int LED_PIN);
    ~ControllerLED();

    void on();
    void off();
    void toggle();
    bool is_on();

private:

    int pin;
    bool active;

};

#endif