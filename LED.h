#ifndef GC_LED_H
#define GC_LED_H

#include <Arduino.h>

class LED {

public:

    LED(int LED_PIN);
    ~LED();

    void on();
    void off();
    void toggle();
    bool is_on();

private:

    int pin;
    bool active;

};

#endif