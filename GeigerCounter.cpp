#include "GeigerCounter.h"

unsigned int GeigerCounter::count = 0;
unsigned int GeigerCounter::cpm = 0;
unsigned int GeigerCounter::multiplier = 0;
unsigned long GeigerCounter::previous_ms = 0;
BluetoothServer* GeigerCounter::bluetoothServer = nullptr;
LiquidCrystal* GeigerCounter::lcd = nullptr;
BLEState GeigerCounter::bleState = WAIT;

void GeigerCounter::setup(int GEIGER_PIN, BluetoothServer* server, LiquidCrystal* display) {

    multiplier = GC_MAX_PERIOD / GC_LOG_PERIOD;
    bluetoothServer = server;
    lcd = display;

    attachInterrupt(digitalPinToInterrupt(GEIGER_PIN), impulse, FALLING);

}

void GeigerCounter::loop() {
    unsigned long current_ms = millis();
    if(current_ms - previous_ms > GC_LOG_PERIOD) {
        previous_ms = current_ms;
        cpm = count * multiplier;

        //lcd->begin(16,2);
        //lcd->print("CPM: ");
        //lcd->print(cpm);
        //lcd->setCursor(0,1);
        //lcd->print("mSv/h: ");
        //lcd->print(get_microsievert());
        Serial.print("CPM: ");
        Serial.println(cpm);
        Serial.print("mSv/h: ");
        Serial.println(get_microsievert());
        count = 0;
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
    Serial.println("Impulse");
    count++;
}

unsigned int GeigerCounter::get_counts_per_minute() {
    return cpm;
}

float GeigerCounter::get_microsievert() {
    float msv = (cpm/151.0);
    return msv;
}

