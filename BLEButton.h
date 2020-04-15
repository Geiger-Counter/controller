#ifndef BLEButton_H
#define BLEButton_H

#include <Arduino.h>
#include "GeigerCounter.h"

class BLEButton {

public:

    BLEButton(int BTN_PIN);
    ~BLEButton();

private:

    static void impulse();

};

#endif