#ifndef GCButton_H
#define GCButton_H

#include <Arduino.h>

class GCButton {

public:

    GCButton(int BTN_PIN, void callback(void));
    ~GCButton();

};

#endif