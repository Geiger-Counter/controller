#ifndef GEIGERCOUNTER_CHARACTERISTIC_CALLBACK_HANDLER_H
#define GEIGERCOUNTER_CHARACTERISTIC_CALLBACK_HANDLER_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include "BLEUUIDs.h"
#include "./../Settings.h"

class CharacteristicCallbackHandler : public BLECharacteristicCallbacks
{

public:

    CharacteristicCallbackHandler(struct Settings* settings);
    ~CharacteristicCallbackHandler();
    void onWrite(BLECharacteristic* characteristic);

private:

    struct Settings* settings;

};

#endif