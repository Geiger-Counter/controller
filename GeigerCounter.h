#ifndef GeigerCounter_H
#define GeigerCounter_H

#include <Arduino.h>
#include <SPI.h>

#define GC_LOG_PERIOD 15000
#define GC_MAX_PERIOD 60000

    class GeigerCounter {

    private:

        static int GEIGER_PIN;
        static unsigned int count;
        static unsigned int cpm;
        static unsigned int multiplier;
        static unsigned long previous_ms;

        static void impulse();

    public:

        static float get_microsievert();
        static unsigned int get_counts_per_minute();
        static void setup(int GEIGER_PIN);
        static void loop();

    };

#endif