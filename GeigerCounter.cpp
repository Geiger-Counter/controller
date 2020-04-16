#include "GeigerCounter.h"

unsigned int GeigerCounter::cpm = 0;
unsigned long GeigerCounter::previous_ms = 0;
BluetoothServer* GeigerCounter::bluetoothServer = nullptr;
LiquidCrystal* GeigerCounter::lcd = nullptr;
BLEState GeigerCounter::bleState = WAIT;
LinkedList<long> GeigerCounter::detections = LinkedList<long>();

void GeigerCounter::setup(int GEIGER_PIN, BluetoothServer* server, LiquidCrystal* display) {

    bluetoothServer = server;
    lcd = display;

    attachInterrupt(digitalPinToInterrupt(GEIGER_PIN), impulse, FALLING);

}

void GeigerCounter::loop() {
    unsigned long current_ms = millis();
    if(current_ms - previous_ms > GC_LOG_PERIOD) {
        previous_ms = current_ms;
        int size = detections.size();
        if(size > 2) {
            // Multiplier = 60 sec / ((timestamp_last_detection - timestamp_first_detection) / 1000 ms)
            float multiplier = 60.0 / ((detections.get(size - 1) - detections.get(0)) / 1000.0);
            cpm = size * multiplier;

            Serial.print("CPM: ");
            Serial.println(cpm);
            Serial.print("mSv/h: ");
            Serial.println(get_microsievert());
        }
    }
    switch(bleState) {
        case START:
            bluetoothServer->start();
            bleState = WAIT;
            break;
        case STOP:
            bluetoothServer->stop();
            bleState = WAIT;
            break;
        default:
            break;
    }
}

void GeigerCounter::start_bluetooth() {
    bleState = START;
}

void GeigerCounter::stop_bluetooth() {
    bleState = STOP;
}

void GeigerCounter::toggle_bluetooth() {
    if(bluetoothServer->is_active()) {
        stop_bluetooth();
    } else {
        start_bluetooth();
    }
}

void GeigerCounter::impulse() {
    detections.add(millis());
}

unsigned int GeigerCounter::get_counts_per_minute() {
    return cpm;
}

float GeigerCounter::get_microsievert() {
    float msv = (cpm/151.0);
    return msv;
}

