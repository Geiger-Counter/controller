#ifndef BluetoothServer_H
#define BluetoothServer_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "BLECallbackHandler.h"

#define SERVICE_UUID "02ed48d7-69b1-4603-9899-a05aa175f9d6"
#define MSV_CHAR_UUID "caf31b35-b140-489f-b875-36893157d6cf"
#define MSV_DESC_UUID "3065e35b-5433-44cb-96f4-215887e225a3"
#define CPM_CHAR_UUID "a4596a0a-a378-49e4-9256-1abfe5784fbd"
#define CPM_DEC_UUID "5b4e4513-2aa3-4180-b155-c1e3a720a756"

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

    BluetoothServer( bool start = false);
    ~BluetoothServer();

    void send_data(float msvh, int cpm);
    void start();
    void stop();
    bool is_active();

private:

    BLECharacteristic* cpm;
    BLECharacteristic* msvh;
    BLECallbackHandler* handler;
    bool active;
    char* ble_code;

    BLECharacteristic* create_ble_characteristic(BLEService* service, char* char_uuid, char* desc_uuid, char* name, int start = 0);

};

#endif
