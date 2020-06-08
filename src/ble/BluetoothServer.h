#ifndef GEIGERCOUNTER_BLUETOOTH_SERVER_H
#define GEIGERCOUNTER_BLUETOOTH_SERVER_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "ServiceCallbackHandler.h"
#include "CharacteristicCallbackHandler.h"
#include "BLEUUIDs.h"

/**
 * BluetoothServer Class
 *
 * Callback Handler for BLEServer
 *
 * on impulse, set the characteristics value to ms since start
 *
 */

class BluetoothServer
{

public:

    BluetoothServer(struct Settings* settings, bool start = false);
    ~BluetoothServer();

    void send_data(float msvh, int cpm);
    void decay_impulse(unsigned long timestamp);
    void start();
    void stop();
    bool is_active();

private:

    struct Settings* settings;

    BLEServer* server;
    BLECharacteristic* cpm;
    BLECharacteristic* msvh;
    BLECharacteristic* impulse;
    BLECharacteristic* ssid;
    BLECharacteristic* password;
    BLECharacteristic* auditive;
    BLECharacteristic* endpoint;
    BLECharacteristic* username;
    BLECharacteristic* token;
    ServiceCallbackHandler* serviceHandler;
    CharacteristicCallbackHandler* characteristicHandler;
    bool active;
    char* ble_code;

    BLECharacteristic* create_ble_characteristic(BLEService* service, char* char_uuid, char* desc_uuid, char* name, int start = 0);
    void build_characteristics(BLEService* api, BLEService* settings);

};

#endif
