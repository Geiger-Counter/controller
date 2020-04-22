#include "GCApplication.h"

GCApplication::GCApplication() {}

GCApplication::~GCApplication() {}

void GCApplication::setup() {

    Serial.begin(9600);
    Serial.println("GeigerCounter started");

    BluetoothServer* serverPtr = new BluetoothServer();
    Display::setup();

    bleButton = new BLEButton(BLUETOOTH_BTN_PIN);
    //greenLED = new LED(GREEN_LED_PIN);
    //redLED = new LED(RED_LED_PIN);

    //greenLED->on();

    GeigerCounter::setup(GEIGER_COUNTER_PIN, serverPtr);

}

void GCApplication::loop() {
    Display::loop();
    GeigerCounter::loop();
}