#include "GC_LED.h"

GC_LED::GC_LED(int GC_LED_PIN) {

    pin = GC_LED_PIN;
    active = false;
    pinMode(GC_LED_PIN, OUTPUT);

}

GC_LED::~GC_LED() {}

void GC_LED::on() {

    digitalWrite(pin, HIGH);
    active = true;

}

void GC_LED::off() {

    digitalWrite(pin, LOW);
    active = false;

}

void GC_LED::toggle() {
    active ? this->off() : this->on();
}

bool GC_LED::is_on() {
    return active;
}