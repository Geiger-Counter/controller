#include "GeigerCounter.h"

volatile int GeigerCounter::isr[3] = {0,0,0};

GeigerCounter::GeigerCounter() {
    greenLED = nullptr;
    redLED = nullptr;
    bleButton = nullptr;
    wifiButton = nullptr;
    toggleButton = nullptr;
}

GeigerCounter::~GeigerCounter() {}

void GeigerCounter::setup() {
    Serial.begin(115200);
    Serial.println("GeigerCounter started");

    Settings* settings = load_settings();

    BluetoothServer* serverPtr = new BluetoothServer(settings);
    ControllerDisplay::setup();

    bleButton = new ControllerButton(BLUETOOTH_BTN_PIN, []() {
        GeigerCounter::execute_isr(0);
    });
    wifiButton = new ControllerButton(WIFI_BTN_PIN, []() {
        GeigerCounter::execute_isr(1);
    });
    toggleButton = new ControllerButton(TOGGLE_BTN_PIN, []() {
        GeigerCounter::execute_isr(2);
    });
    greenLED = new ControllerLED(GREEN_LED_PIN);
    redLED = new ControllerLED(RED_LED_PIN);

    greenLED->on();

    MainHandler::setup(GEIGER_COUNTER_PIN, settings, serverPtr, nullptr);
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
                case 1: MainHandler::toggle_wifi();
                    break;
                case 2: ControllerDisplay::toggleState();
                    break;
                default: break;          
            }
            GeigerCounter::isr[i] = 0;
        }
    }
}