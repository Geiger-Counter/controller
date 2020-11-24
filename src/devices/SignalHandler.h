#ifndef GEIGERCOUNTER_CONTROLLER_SIGNAL_HANDLER
#define GEIGERCOUNTER_CONTROLLER_SIGNAL_HANDLER

#include <Arduino.h>

class SignalHandler {

public:

    SignalHandler(int PIN);
    ~SignalHandler();

    void loop();
    void impulse(int interval, int times);

    void on();
    void off();
    void toggle();

    bool is_active();

private:

    bool active;
    bool determined;
    int PIN;
    int interval;
    int times;
    int state;
    unsigned long previous;

};

#endif