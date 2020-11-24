#include "./src/GeigerCounter.h"

#define BLUETOOTH_BTN_PIN 22
#define SIGNAL_TOGGLE_BTN_PIN 19

#define SIGNAL_PIN 39
#define R_PIN 36
#define G_PIN 37
#define B_PIN 38

#define GEIGER_COUNTER_PIN 18

GeigerCounter app;

void setup() {
  app.setup(GEIGER_COUNTER_PIN, BLUETOOTH_BTN_PIN, SIGNAL_TOGGLE_BTN_PIN, SIGNAL_PIN, R_PIN, G_PIN, B_PIN);
}

void loop() {
  app.loop();
}