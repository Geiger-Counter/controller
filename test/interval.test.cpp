#include <stdio.h>
#include "./../src/devices/IntervalHandler.h"

void setup() {
    IntervalHandler::add(1000, -1, [](int times) {
        printf("Running again\n");
    });
}

void loop() {
    IntervalHandler::loop();
}

int main() {
    setup();
    while(true) {
        loop();
    }
}