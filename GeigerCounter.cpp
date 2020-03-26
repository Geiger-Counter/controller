#include "GeigerCounter.h"

unsigned int GeigerCounter::count = 0;
unsigned int GeigerCounter::cpm = 0;
unsigned int GeigerCounter::multiplier = 0;
unsigned long GeigerCounter::previous_ms = 0;
BluetoothServer* GeigerCounter::bluetoothServer = nullptr;

void GeigerCounter::setup(int GEIGER_PIN, BluetoothServer* server) {

    multiplier = GC_MAX_PERIOD / GC_LOG_PERIOD;
    bluetoothServer = server;

    attachInterrupt(digitalPinToInterrupt(GEIGER_PIN), impulse, FALLING);

}

void GeigerCounter::loop() {
    unsigned long current_ms = millis();
    if(current_ms - previous_ms > GC_LOG_PERIOD) {
        previous_ms = current_ms;
        cpm = count * multiplier;

        Serial.print("CPM: ");
        Serial.println(cpm);
        Serial.print("mSv/h: ");
        Serial.println(get_microsievert());
        count = 0;
    }
}

void GeigerCounter::impulse() {
    Serial.println("Impulse");
    count++;
    bluetoothServer->impulse();
}

unsigned int GeigerCounter::get_counts_per_minute() {
    return cpm;
}

float GeigerCounter::get_microsievert() {
    float msv = (cpm/151.0);
    return msv;
}

