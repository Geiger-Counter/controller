#include "ControllerRGBLED.h"

ControllerRGBLED::ControllerRGBLED(int R_PIN, int G_PIN, int B_PIN) {
    this->r_pin = R_PIN;
    this->g_pin = G_PIN;
    this->b_pin = B_PIN;

    this->active = false;

    pinMode(r_pin, OUTPUT);
    pinMode(g_pin, OUTPUT);
    pinMode(b_pin, OUTPUT);
}

ControllerRGBLED::~ControllerRGBLED() {}

void ControllerRGBLED::on(bool r, bool g, bool b) {
    digitalWrite(r_pin, 255 * (int)r);
    digitalWrite(g_pin, 255 * (int)g);
    digitalWrite(b_pin, 255 * (int)b);
    this->active = true;
}

void ControllerRGBLED::off() {
    digitalWrite(r_pin, 0);
    digitalWrite(g_pin, 0);
    digitalWrite(b_pin, 0);
    this->active = false;
}

void ControllerRGBLED::green() {
    this->on(false, true, false);
}

void ControllerRGBLED::yellow() {
    this->on(true, true, false);
}

void ControllerRGBLED::red() {
    this->on(true, false, false);
}

void ControllerRGBLED::blue() {
    this->on(false, false, true);
}

bool ControllerRGBLED::is_on() {
    return this->active;
}