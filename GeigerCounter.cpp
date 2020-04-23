#include "GeigerCounter.h"

unsigned int GeigerCounter::cpm = 0;
unsigned long GeigerCounter::previous_ms = 0;
BluetoothServer* GeigerCounter::bluetoothServer = nullptr;
BLEState GeigerCounter::bleState = WAIT;
LinkedList<long> GeigerCounter::detections = LinkedList<long>();

void GeigerCounter::setup(int GEIGER_PIN, BluetoothServer* server) {

    bluetoothServer = server;

    attachInterrupt(digitalPinToInterrupt(GEIGER_PIN), impulse, FALLING);

}

void GeigerCounter::loop() {
    unsigned long current_ms = millis();
    if(current_ms - previous_ms > GC_LOG_PERIOD) {
        previous_ms = current_ms;
        int size = detections.size();
        float multiplier = get_multiplier();
        cpm = size * multiplier;

        Serial.print("CPM: ");
        Serial.println(cpm);
        Serial.print("mSv/h: ");
        Serial.println(get_microsievert());
        bluetoothServer->send_data(get_microsievert(), cpm);
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
    Display::toggleBLE();
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

float GeigerCounter::get_multiplier() {
    // only last 500 entries
    int size = detections.size();
    // need a minimum of 5 detections to get a "good" calculation on startup
    if(size > 5) {
        int start = size > GC_LOG_SIZE ? size - 500 : 0;
        // Multiplier = 60 sec / ((timestamp_last_detection - timestamp_start_of_detection) / 1000 ms)
        return 60.0 / ((detections.get(size - 1)- detections.get(start)) / 1000.0);
    }
    return 1.0;
}

