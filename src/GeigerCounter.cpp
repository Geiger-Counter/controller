#include "GeigerCounter.h"

GeigerCounter::GeigerCounter() {
    greenLED = nullptr;
    redLED = nullptr;
    bleButton = nullptr;
    wifiButton = nullptr;
    toggleButton = nullptr;
}

GeigerCounter::~GeigerCounter() {}

void GeigerCounter::setup() {

    Serial.begin(9600);
    Serial.println("GeigerCounter started");

    struct Settings* settings = load_settings();

    BluetoothServer* serverPtr = new BluetoothServer(settings);
    ControllerDisplay::setup();

    bleButton = new ControllerButton(BLUETOOTH_BTN_PIN, []() {
        Serial.println("Button BLE Click");
        MainHandler::toggle_bluetooth();
    });
    wifiButton = new ControllerButton(WIFI_BTN_PIN, []() {
        MainHandler::toggle_wifi();
    });
    toggleButton = new ControllerButton(TOGGLE_BTN_PIN, []() {
        ControllerDisplay::toggleState();
    });
    greenLED = new ControllerLED(GREEN_LED_PIN);
    redLED = new ControllerLED(RED_LED_PIN);

    greenLED->on();

    MainHandler::setup(GEIGER_COUNTER_PIN, settings, serverPtr, nullptr);

}

void GeigerCounter::loop() {
    ControllerDisplay::loop();
    MainHandler::loop();
}