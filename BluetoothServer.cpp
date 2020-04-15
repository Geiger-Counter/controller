#include "BluetoothServer.h"

BluetoothServer::BluetoothServer(bool start) {

    active = false;
    if(start) {
        BluetoothServer::start();
    }

}

BluetoothServer::~BluetoothServer() {};

void BluetoothServer::start() {

    if(!active) {
        active = true;
        BLEDevice::init("GeigerCounter BT Server");
        Serial.println("BluetoothServer starting...");
        BLEServer* server = BLEDevice::createServer();

        handler = new BLECallbackHandler();
        server->setCallbacks(handler);

        /**
         * Create a new BLE service for providing impulse values
         */
        BLEService* cpmService = server->createService(SERVICE_UUID);
        cpm = new BLECharacteristic(
                CHAR_UUID,
                BLECharacteristic::PROPERTY_READ |
                BLECharacteristic::PROPERTY_NOTIFY
        );
        BLEDescriptor* cpmDesc = new BLEDescriptor(DESC_UUID);

        cpmService->addCharacteristic(cpm);
        char buf[16];
        long time = 0;
        ltoa(time, buf, 10);
        cpmDesc->setValue(buf);
        cpm->addDescriptor(cpmDesc);
        cpm->addDescriptor(new BLE2902());

        cpmService->start();
        BLEAdvertising* advertising = BLEDevice::getAdvertising();
        advertising->addServiceUUID(SERVICE_UUID);
        advertising->setScanResponse(true);
        advertising->setMinPreferred(0x06);
        advertising->setMinPreferred(0x12);
        BLEDevice::startAdvertising();

        Serial.println("BluetoothServer running");
    }

}

void BluetoothServer::stop() {
    if(active) {
        Serial.println("Stopping Bluetooth Server ...");
        BLEDevice::deinit(true);
        cpm = nullptr;
        handler = nullptr;
        active = false;
        Serial.println("BluetoothServer stopped");
    }
}

bool BluetoothServer::is_active() {
    return active;
}

void BluetoothServer::send_data(float msvh) {
    if(active) {
        if(handler->isConnected()) {
            char buf[16];
            ltoa(msvh, buf, 10);
            cpm->setValue(buf);
            cpm->notify();
        }
    }
}

