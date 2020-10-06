#ifndef GEIGERCOUNTER_CONTROLLER_BATTERY_H
#define GEIGERCOUNTER_CONTROLLER_BATTERY_H

#include <Arduino.h>

class ControllerBattery {

public:

    ControllerBattery();
    ~ControllerBattery();

    float get_percentage();
    bool is_loading();

private:

    bool loading;

};

#endif