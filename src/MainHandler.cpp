#include "MainHandler.h"

int MainHandler::cpm = 0;
unsigned long MainHandler::previous_ms = 0;
BluetoothServer* MainHandler::bluetoothServer = nullptr;
ButtonState MainHandler::bleState = WAIT;
ButtonState MainHandler::wifiState = WAIT;
LinkedList<long> MainHandler::detections = LinkedList<long>();
WiFiHandler* MainHandler::wifiHandler = nullptr;
struct Settings* MainHandler::settings = nullptr;

void MainHandler::setup(int GEIGER_PIN, struct Settings* settings, BluetoothServer* server, WiFiHandler *handler) {

    bluetoothServer = server;
    wifiHandler = handler;
    settings = settings;

    attachInterrupt(digitalPinToInterrupt(GEIGER_PIN), impulse, FALLING);

}

void MainHandler::loop() {
    unsigned long current_ms = millis();
    if(current_ms - previous_ms > GC_LOG_PERIOD) {
        //send_data(settings, &detections);
        previous_ms = current_ms;
        cpm = calculate_cpm(&detections);

        Serial.print("CPM: ");
        Serial.print(cpm);
        Serial.print(" | mSv/h: ");
        Serial.println(calculate_msvh(cpm));
        bluetoothServer->send_data(calculate_msvh(cpm), cpm);
        if(wifiState == RUNNING) {
            //API::send_data()
        }
    }
    switch(bleState) {
        case START:
            bluetoothServer->start();
            ControllerDisplay::showBLE();
            bleState = WAIT;
            break;
        case STOP:
            bluetoothServer->stop();
            ControllerDisplay::hideBLE();
            bleState = WAIT;
            break;
        default:
            break;
    }
    switch(wifiState) {
        case START:
            wifiHandler->on();
            ControllerDisplay::showWiFi();
            wifiState = RUNNING;
            break;
        case STOP:
            wifiHandler->off();
            ControllerDisplay::hideWiFi();
            wifiState = WAIT;
            break;
        default:
            break;
    }
}

void MainHandler::start_bluetooth() {
    bleState = START;
}

void MainHandler::stop_bluetooth() {
    bleState = STOP;
}

void MainHandler::toggle_bluetooth() {
    if(bluetoothServer->is_active()) {
        stop_bluetooth();
    } else {
        start_bluetooth();
    }
}

void MainHandler::start_wifi() {
    wifiState = START;
}

void MainHandler::stop_wifi() {
    wifiState = STOP;
}

void MainHandler::toggle_wifi() {
    if(wifiHandler->is_connected()) {
        stop_wifi();
    } else {
        start_wifi();
    }
}

struct Settings* MainHandler::get_settings() {
    return settings;
}

void MainHandler::impulse() {
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

