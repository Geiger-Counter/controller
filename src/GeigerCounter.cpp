#include "GeigerCounter.h"

volatile int GeigerCounter::isr[3] = {0,0,0};

GeigerCounter::GeigerCounter() {
    bleButton = nullptr;
    signalButton = nullptr;
}

GeigerCounter::~GeigerCounter() {}

void GeigerCounter::setup(int IMP_PIN, int BLE_BTN_PIN, int SGN_BTN_PIN, int SNG_PIN, int R_PIN, int B_PIN, int G_PIN) {
    Serial.begin(115200);
    Serial.println("GeigerCounter started");

    BluetoothServer* serverPtr = new BluetoothServer();
    ControllerDisplay::setup();

    bleButton = new ControllerButton(BLE_BTN_PIN, []() {
        GeigerCounter::execute_isr(0);
    });

    signalButton = new ControllerButton(SGN_BTN_PIN, []() {
        GeigerCounter::execute_isr(1);
    });

    MainHandler::setup(IMP_PIN, SNG_PIN, R_PIN, B_PIN, G_PIN, serverPtr);
}

void GeigerCounter::loop() {
    GeigerCounter::check_isr();
    ControllerDisplay::loop();
    MainHandler::loop();
}

void IRAM_ATTR GeigerCounter::execute_isr(int index) {
    GeigerCounter::isr[index] = 1;
}

void GeigerCounter::check_isr() {
    for(int i = 0; i < 3; i++) {
        if(GeigerCounter::isr[i] == 1) {
            switch(i) {
                case 0: MainHandler::toggle_bluetooth();
                    break;
                case 1: MainHandler::toggle_signal();
                    break;
                default: break;          
            }
            GeigerCounter::isr[i] = 0;
        }
    }
}