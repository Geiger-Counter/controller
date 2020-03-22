#ifndef PowerButton_H
#define PowerButton_H

#include <Arduino.h>
#include "GCButton.h"
#include "LED.h"

class PowerButton {

public:

    PowerButton(int BTN_PIN);
    ~PowerButton();

private:

    GCButton button;

};

#endif