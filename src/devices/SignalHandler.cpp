#include "SignalHandler.h"

int SignalHandler::DELAY = 500;

SignalHandler::SignalHandler(int _PIN) {
    this->PIN = _PIN;
    this->active = false;
    this->last_action = millis();

    pinMode(this->PIN, OUTPUT);
}

SignalHandler::~SignalHandler() {}

void SignalHandler::on() {
    Serial.println("Show Signal");
    this->active = true;
}

void SignalHandler::off() {
    Serial.println("Hide Signal");
    this->active = false;
}

void SignalHandler::toggle() {
    unsigned long now = millis();
    if((now - this->last_action) > SignalHandler::DELAY) {
        this->last_action = now;
        this->active ? this->off() : this->on();
    } 
}

void SignalHandler::impulse(int _interval = 1000) {
    this->start = millis();
    this->interval = _interval;
    this->started = true;
}

void SignalHandler::loop() {
    if(this->active && this->started) {
        unsigned long now = millis();
        if((now - this->start) > this->interval) {
            this->started = false;
        }
        digitalWrite(this->PIN, this->started ? HIGH : LOW);
    }
}

bool SignalHandler::is_active() {
    return this->active;
}