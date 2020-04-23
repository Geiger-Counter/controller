#include "GCButton.h"

GCButton::GCButton(int BTN_PIN, void callback(void)) {

    pinMode(BTN_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(BTN_PIN), callback, FALLING);
}

GCButton::~GCButton() {}