#include "BLEButton.h"

BLEButton::BLEButton(int BTN_PIN) {
    pinMode(BTN_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(BTN_PIN), impulse, FALLING);
}

void BLEButton::impulse() {
    Serial.println("Click");
    GeigerCounter::toggle_bluetooth();
}

BLEButton::~BLEButton() {}