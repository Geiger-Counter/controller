#include "./src/GeigerCounter.h"

#define SIGNAL_PIN 23
#define R_PIN 19
#define G_PIN 22
#define B_PIN 21

#define GEIGER_COUNTER_PIN 18

GeigerCounter app;

void setup() {

  app.setup(GEIGER_COUNTER_PIN, SIGNAL_PIN, R_PIN, G_PIN, B_PIN);
}

void loop() {
  app.loop();

}