#include "SignalHandler.h"

SignalHandler::SignalHandler(int _PIN) {
    this->PIN = _PIN;

    pinMode(this->PIN, OUTPUT);
}

SignalHandler::~SignalHandler() {}

void SignalHandler::impulse(int _interval = 1000) {
    this->start = millis();
    this->interval = _interval;
    this->started = true;
}

void SignalHandler::loop() {
    if(this->started) {
        unsigned long now = millis();
        if((now - this->start) > this->interval) {
            this->started = false;
        }
        digitalWrite(this->PIN, this->started ? HIGH : LOW);
    }
}