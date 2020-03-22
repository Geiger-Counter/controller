#include "GCButton.h"

GCButton::GCButton(int BTN_PIN, void push_func())
{

    pinMode(BTN_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(BTN_PIN), push_func, FALLING);

}

GCButton::~GCButton() {}