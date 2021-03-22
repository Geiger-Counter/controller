#include "ControllerRGBLED.h"

ControllerRGBLED::ControllerRGBLED(int R_PIN, int G_PIN, int B_PIN) {
    this->r_pin = R_PIN;
    this->g_pin = G_PIN;
    this->b_pin = B_PIN;

    this->active = false;

    pinMode(this->r_pin, OUTPUT);
    pinMode(this->g_pin, OUTPUT);
    pinMode(this->b_pin, OUTPUT);
}

ControllerRGBLED::~ControllerRGBLED() {}

void ControllerRGBLED::on(bool r, bool g, bool b) {
    digitalWrite(this->r_pin, r ? HIGH : LOW);
    digitalWrite(this->g_pin, g ? HIGH : LOW);
    digitalWrite(this->b_pin, b ? HIGH : LOW);
    this->active = true;
}

void ControllerRGBLED::off() {
    digitalWrite(this->r_pin, 0);
    digitalWrite(this->g_pin, 0);
    digitalWrite(this->b_pin, 0);
    this->active = false;
}

void ControllerRGBLED::green() {
    this->on(false, false, true);
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