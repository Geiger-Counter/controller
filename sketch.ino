#include "GeigerCounter.h"
//#include "PowerButton.h"
//#include "LED.h"
#include "BluetoothServer.h"

#define BLUETOOTH_BTN_PIN 27
#define POWER_BTN_PIN 26
#define GREEN_LED_PIN 12
#define RED_LED_PIN 14
#define GEIGER_PIN 21

//PowerButton pb (POWER_BTN_PIN);
//LED green(GREEN_LED_PIN);
//LED red(RED_LED_PIN);

void setup() {

    Serial.begin(9600);
    Serial.println("Running");
    BluetoothServer* blServer = new BluetoothServer();
    GeigerCounter::setup(GEIGER_PIN, blServer);
    //green.on();

}

void loop() {
    GeigerCounter::loop();
}