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
    void blink(int interval, int times);
    void loop();
    bool is_on();

private:

    int pin;
    bool active;
    bool blinking;
    int interval;
    int times;
    int state;
    unsigned long previous;

};

#endif