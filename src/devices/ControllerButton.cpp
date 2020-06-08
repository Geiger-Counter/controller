#include "ControllerButton.h"

ControllerButton::ControllerButton(int BTN_PIN, void callback(void)) {

    pinMode(BTN_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(BTN_PIN), callback, FALLING);
}

ControllerButton::~ControllerButton() {}