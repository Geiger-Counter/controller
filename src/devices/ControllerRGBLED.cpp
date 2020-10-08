#include "ControllerRGBLED.h"

ControllerRGBLED::ControllerRGBLED(int R_PIN, int G_PIN, int B_PIN) {
    r_pin = R_PIN;
    g_pin = G_PIN;
    b_pin = B_PIN;

    active = false;

    pinMode(r_pin, OUTPUT);
    pinMode(g_pin, OUTPUT);
    pinMode(b_pin, OUTPUT);
}

ControllerRGBLED::~ControllerRGBLED() {}

void ControllerRGBLED::on(bool r, bool g, bool b) {
    digitalWrite(r_pin, 255 * (int)r);
    digitalWrite(g_pin, 255 * (int)g);
    digitalWrite(b_pin, 255 * (int)b);
    active = true;
}

void ControllerRGBLED::off() {
    digitalWrite(r_pin, 0);
    digitalWrite(g_pin, 0);
    digitalWrite(b_pin, 0);
    active = false;
}

bool ControllerRGBLED::is_on() {
    return active;
}