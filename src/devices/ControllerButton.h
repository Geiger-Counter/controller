#ifndef GEIGERCOUNTER_CONTROLLER_BUTTON_H
#define GEIGERCOUNTER_CONTROLLER_BUTTON_H

#include <Arduino.h>

class ControllerButton {

public:

    ControllerButton(int BTN_PIN, void callback(void));
    ~ControllerButton();

};

#endif