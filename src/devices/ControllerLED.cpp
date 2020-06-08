#include "ControllerLED.h"

ControllerLED::ControllerLED(int LED_PIN) {
    pin = LED_PIN;
    active = false;
    pinMode(LED_PIN, OUTPUT);
}

ControllerLED::~ControllerLED() {}

void ControllerLED::on() {
    digitalWrite(pin, HIGH);
    active = true;
}

void ControllerLED::off() {
    digitalWrite(pin, LOW);
    active = false;
}

void ControllerLED::toggle() {
    active ? this->off() : this->on();
}

bool ControllerLED::is_on() {
    return active;
}