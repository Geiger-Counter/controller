# GeigerCounter

## Install

Clone repository in Arduino libraries folder:

````shell script
git clone git@github.com:mc17uulm/GeigerCounter.git
````

## Usage

### Arduino IDE
````c++
#include <GeigerCounter.h>

#define GEIGER_PIN 2

void setup() {

    Serial.begin(9600);
    GeigerCounter::setup(GEIGER_PIN);

}

void loop() {
    GeigerCounter::loop();
}
````
### Functions

#### Get counts per minute
````c++
unsigned int cpm = GeigerCounter::get_counts_per_minute();
````

#### Get &micro;Sv/h
````c++
float msv = GeigerCounter::get_microsievert();
````

