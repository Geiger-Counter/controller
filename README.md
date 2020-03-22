# GeigerCounter

## Install

Clone repository in Arduino libraries folder:

````shell script
git clone git@github.com:mc17uulm/GeigerCounter.git
````

## Usage

### Arduino IDE
````c++
#include "GeigerCounter.h"
#include "PowerButton.h"
#include "LED.h"

#define BLUETOOTH_BTN_PIN 27
#define POWER_BTN_PIN 26
#define GREEN_LED_PIN 12
#define RED_LED_PIN 14
#define GEIGER_PIN 21

PowerButton pb (POWER_BTN_PIN);
LED green(GREEN_LED_PIN);
LED red(RED_LED_PIN);

void setup() {

  Serial.begin(9600);
  GeigerCounter::setup(GEIGER_PIN, ControllerType::ESP32_CONTROLLER);
  green.on();

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

