#include "GeigerCounter.h"

GeigerCounter::GeigerCounter() {}

GeigerCounter::~GeigerCounter() {}

void GeigerCounter::setup(int IMP_PIN, int SNG_PIN, int R_PIN, int G_PIN, int B_PIN) {
    Serial.begin(115200);
    Serial.println("GeigerCounter started");

    BluetoothServer* serverPtr = new BluetoothServer();
    ControllerDisplay::setup();

    MainHandler::setup(IMP_PIN, SNG_PIN, R_PIN, G_PIN, B_PIN, serverPtr);
}

void GeigerCounter::loop() {
    ControllerDisplay::loop();
    MainHandler::loop();
}