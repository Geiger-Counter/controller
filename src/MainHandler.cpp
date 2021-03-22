#include "MainHandler.h"

int MainHandler::cpm = 0;
unsigned long MainHandler::previous_ms = 0;
BluetoothServer* MainHandler::bluetoothServer = nullptr;
ButtonState MainHandler::bleState = WAIT;
LinkedList<long> MainHandler::detections = LinkedList<long>();
ControllerRGBLED* MainHandler::rgbLED = nullptr;
SignalHandler* MainHandler::signalHandler = nullptr;

void MainHandler::setup(int IMP_PIN, int SGN_PIN, int R_PIN, int B_PIN, int G_PIN, BluetoothServer* server) {

    bluetoothServer = server;
    rgbLED = new ControllerRGBLED(R_PIN, G_PIN, B_PIN);
    signalHandler = new SignalHandler(SGN_PIN);

    attachInterrupt(digitalPinToInterrupt(IMP_PIN), impulse, FALLING);

}

void MainHandler::loop() {
    signalHandler->loop();
    unsigned long current_ms = millis();
    if(current_ms - previous_ms > GC_LOG_PERIOD) {
        previous_ms = current_ms;
        cpm = calculate_cpm(&detections);
        float msvh = calculate_msvh(cpm);

        if(msvh < 11) {
            rgbLED->green();
        } else if(msvh >= 11 && msvh < 57) {
            rgbLED->yellow();
        } else {
            rgbLED->red();
        }

        Serial.print("CPM: ");
        Serial.print(cpm);
        Serial.print(" | mSv/h: ");
        Serial.println(msvh);
        bluetoothServer->send_data(calculate_msvh(cpm), cpm);
    }
}

void MainHandler::start_bluetooth() {
    bluetoothServer->start();
    Serial.println("Started");
    ControllerDisplay::showBLE();
}

void MainHandler::stop_bluetooth() {
    bluetoothServer->stop();
    ControllerDisplay::hideBLE();
}

void MainHandler::toggle_bluetooth() {
    if(bluetoothServer->is_active()) {
        stop_bluetooth();
    } else {
        start_bluetooth();
    }
}

void MainHandler::toggle_signal() {
    Serial.println("Toggle Signal");
    signalHandler->toggle();
}

void MainHandler::impulse() {
    signalHandler->impulse(100);
    unsigned long time = millis();
    detections.add(time);
    if(detections.size() > 999) {
        detections.shift();
    }
    bluetoothServer->decay_impulse(time);
}

int MainHandler::get_counts_per_minute() {
    return cpm;
}

float MainHandler::get_microsievert() {
    float msv = (cpm/151.0);
    return msv;
}

