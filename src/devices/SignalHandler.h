#ifndef GEIGERCOUNTER_CONTROLLER_SIGNAL_HANDLER
#define GEIGERCOUNTER_CONTROLLER_SIGNAL_HANDLER

#include <Arduino.h>

class SignalHandler {

public:

    SignalHandler(int PIN);
    ~SignalHandler();

    void loop();
    void impulse(int interval);

    void on();
    void off();
    void toggle();

    bool is_active();

private:

    bool active;
    bool started;
    int PIN;
    int interval;
    unsigned long last_action;
    unsigned long start;
    static int DELAY;

};

#endif