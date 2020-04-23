#ifndef GC_LED_H
#define GC_LED_H

#include <Arduino.h>

class GC_LED {

public:

    GC_LED(int LED_PIN);
    ~GC_LED();

    void on();
    void off();
    void toggle();
    bool is_on();

private:

    int pin;
    bool active;

};

#endif