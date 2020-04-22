#ifndef GeigerCounter_H
#define GeigerCounter_H

#include <Arduino.h>
#include <SPI.h>
#include "BluetoothServer.h"
#include "LinkedList.h"

#define GC_LOG_PERIOD 5000

enum BLEState {
    START,
    STOP,
    WAIT
};

class GeigerCounter {

public:

    static void setup(int GEIGER_PIN, BluetoothServer* server);
    static float get_microsievert();
    static unsigned int get_counts_per_minute();
    static void loop();
    static void impulse();
    static void start_bluetooth();
    static void stop_bluetooth();
    static void toggle_bluetooth();

private:

    static unsigned int cpm;
    static unsigned long previous_ms;
    static LinkedList<long> detections;
    static BLEState bleState;
    static BluetoothServer* bluetoothServer;


};

#endif