#ifndef GEIGERCOUNTER_BLUETOOTH_SERVER_H
#define GEIGERCOUNTER_BLUETOOTH_SERVER_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "ServiceCallbackHandler.h"
#include "BLEUUIDs.h"

struct CharacteristicTemplate {
    BLEService* service;
    const char* uuid;
    const char* desc_uuid;
    const char* desc;
    const char* default_value;
    bool read;
    bool write;
    bool notify;
};

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

    BluetoothServer(bool start = false);
    ~BluetoothServer();

    void send_data(float msvh, int cpm);
    void decay_impulse(unsigned long timestamp);
    void start();
    void stop();
    bool is_active();

private:

    BLEServer* server;
    BLECharacteristic* cpm;
    BLECharacteristic* msvh;
    BLECharacteristic* impulse;
    ServiceCallbackHandler* serviceHandler;
    bool active;
    char* ble_code;

    BLECharacteristic* create_ble_characteristic(struct CharacteristicTemplate tmpl);
    void build_characteristics(BLEService* api, BLEService* settings);

};

#endif
