#include "ControllerLED.h"

ControllerLED::ControllerLED(int LED_PIN) {
    pin = LED_PIN;

    interval = 1000;
    times = 1;

    active = false;
    blinking = false;

    state = LOW;

    pinMode(LED_PIN, OUTPUT);
}

ControllerLED::~ControllerLED() {}

void ControllerLED::on() {
    digitalWrite(pin, HIGH);
    active = true;
}

void ControllerLED::off() {
    digitalWrite(pin, LOW);
    blinking = false;
    active = false;
}

void ControllerLED::toggle() {
    active ? this->off() : this->on();
}

void ControllerLED::blink(int _interval = 1000, int _times = 1) {
    previous = 0;
    interval = _interval;
    times = _times;
    state = LOW;
    blinking = true;
}

void ControllerLED::loop() {
    if(blinking) {
        if(times == 0) {
            off();
        } else {
            unsigned long now = millis();
            if((now - previous) > interval) {
                previous = now;
                if(times != -1) {
                    times--;
                }
                if(state == LOW) {
                    state = HIGH;
                    on();
                } else {
                    state = LOW;
                    off();
                }
            }
        }
    }
}

bool ControllerLED::is_on() {
    return active;
}