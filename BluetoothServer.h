#ifndef BluetoothServer_H
#define BluetoothServer_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "BLECallbackHandler.h"

#define SERVICE_UUID "cd8e6468-20b4-40bd-89b5-33c53993c4fb"
#define CHAR_UUID "52c9a69c-6078-4011-97d5-f3417c882102"
#define DESC_UUID "90e6d6ca-e868-4943-9b9a-4efd4fdcede9"

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

    BluetoothServer();
    ~BluetoothServer();

    void impulse();

private:

    BLECharacteristic* cpm;
    BLECallbackHandler* handler;
    bool connected;

};

#endif
