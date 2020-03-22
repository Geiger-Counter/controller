#include "LED.h"

LED::LED(int LED_PIN) {

    pin = LED_PIN;
    active = false;
    pinMode(LED_PIN, OUTPUT);

}

LED::~LED() {}

void LED::on() {

    digitalWrite(pin, HIGH);
    active = true;

}

void LED::off() {

    digitalWrite(pin, LOW);
    active = false;

}

void LED::toggle() {
    active ? this->off() : this->on();
}

bool LED::is_on() {
    return active;
}