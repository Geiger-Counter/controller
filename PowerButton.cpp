#include "PowerButton.h"

PowerButton::PowerButton(int BTN_PIN) :  button (
        BTN_PIN,
        [] () {
                Serial.println("PowerBtn Clicked");
        }
) {}

PowerButton::~PowerButton() {}