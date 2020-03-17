#include <GeigerCounter.h>

#define GEIGER_PIN 2

void setup() {

    Serial.begin(9600);
    GeigerCounter::setup(GEIGER_PIN);

}

void loop() {
    GeigerCounter::loop();
}