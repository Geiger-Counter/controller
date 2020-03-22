#ifndef GeigerCounter_H
#define GeigerCounter_H

#include <Arduino.h>
#include <SPI.h>

#define GC_LOG_PERIOD 15000
#define GC_MAX_PERIOD 60000

enum ControllerType {
    ARDUINO_CONTROLLER,
    ESP32_CONTROLLER,
    ESP8266_CONTROLLER
};

class GeigerCounter {

public:

    static float get_microsievert();
    static unsigned int get_counts_per_minute();
    static void setup(int GEIGER_PIN, ControllerType type);
    static void loop();

private:

    static ControllerType type;
    static unsigned int count;
    static unsigned int cpm;
    static unsigned int multiplier;
    static unsigned long previous_ms;

    static void impulse();


};

#endif