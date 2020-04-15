#include "GeigerCounter.h"
#include "BLEButton.h"
#include "LED.h"
#include "BluetoothServer.h"
#include <LiquidCrystal.h>

#define BLUETOOTH_BTN_PIN 12
#define GREEN_LED_PIN 14
#define RED_LED_PIN 27
#define GEIGER_PIN 21
#define RS_LCD_PIN 34
#define ENABLE_LCD_PIN 35
#define D4_LCD_PIN 32
#define D5_LCD_PIN 33
#define D6_LCD_PIN 25
#define D7_LCD_PIN 26

BLEButton btb (BLUETOOTH_BTN_PIN);
LED green(GREEN_LED_PIN);
//LED red(RED_LED_PIN);

LiquidCrystal lcd(RS_LCD_PIN, ENABLE_LCD_PIN, D4_LCD_PIN, D5_LCD_PIN, D6_LCD_PIN, D7_LCD_PIN); 

void setup() {

  Serial.begin(9600);
  Serial.println("Running");
  BluetoothServer* blServer = new BluetoothServer();
  GeigerCounter::setup(GEIGER_PIN, blServer, &lcd);
  green.on();
  lcd.begin(16,2);
  lcd.print("Hello");

}

void loop() {
  GeigerCounter::loop();
}