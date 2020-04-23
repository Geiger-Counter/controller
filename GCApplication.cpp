#include "GCApplication.h"

GCApplication::GCApplication() {
    greenLED = nullptr;
    redLED = nullptr;
}

GCApplication::~GCApplication() {}

void GCApplication::setup() {

    Serial.begin(9600);
    Serial.println("GeigerCounter started");

    BluetoothServer* serverPtr = new BluetoothServer();
    Display::setup();

    bleButton = new GCButton(BLUETOOTH_BTN_PIN, []() {
        GeigerCounter::toggle_bluetooth();
    });
    toggleButton = new GCButton(TOGGLE_BTN_PIN, []() {
        Display::toggleState();
    });
    greenLED = new GC_LED(GREEN_LED_PIN);
    redLED = new GC_LED(RED_LED_PIN);

    greenLED->on();

    GeigerCounter::setup(GEIGER_COUNTER_PIN, serverPtr);

}

void GCApplication::loop() {
    Display::loop();
    GeigerCounter::loop();
}