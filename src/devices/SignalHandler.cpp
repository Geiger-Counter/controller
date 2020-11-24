#include "SignalHandler.h"

SignalHandler::SignalHandler(int _PIN) {
    this->PIN = _PIN;
    this->active = false;

    pinMode(this->PIN, OUTPUT);
}

SignalHandler::~SignalHandler() {}

void SignalHandler::on() {
    this->active = true;
}

void SignalHandler::off() {
    this->active = false;
}

void SignalHandler::toggle() {
    this->active ? this->off() : this->on();
}

void SignalHandler::impulse(int _interval = 1000, int _times = 1) {
    this->previous = 0;
    this->interval = _interval;
    this->times = _times;
    this->state = LOW;
    this->determined = true;
}

void SignalHandler::loop() {
    if(this->active && this->determined) {
        if(this->times == 0) {
            this->off();
        } else {
            unsigned long now = millis();
            if((now - this->previous) > this->interval) {
                this->previous = now;
                if(this->times != -1) {
                    this->times--;
                }
                if(this->state == LOW) {
                    this->state = HIGH;
                    this->on();
                } else {
                    this->state = LOW;
                    this->off();
                }
            }
        }
    }
}

bool SignalHandler::is_active() {
    return this->active;
}