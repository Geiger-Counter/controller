#ifndef GEIGERCOUNTER_CONTROLLER_SIGNAL_HANDLER
#define GEIGERCOUNTER_CONTROLLER_SIGNAL_HANDLER

#include <Arduino.h>

class SignalHandler {

public:

    SignalHandler(int PIN);
    ~SignalHandler();

    void loop();
    void impulse(int interval);

private:

    bool started;
    int PIN;
    int interval;
    unsigned long start;

};

#endif