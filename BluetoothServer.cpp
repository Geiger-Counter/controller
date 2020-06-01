#include "BluetoothServer.h"

BluetoothServer::BluetoothServer(bool start) {

    active = false;

    if(start) {
        BluetoothServer::start();
    }

}

void BluetoothServer::start() {

    if(!active) {
        active = true;
        BLEDevice::init("GeigerCounter BT Server");
        Serial.println("BluetoothServer starting...");
        BLEServer* server = BLEDevice::createServer();

        handler = new BLECallbackHandler();
        server->setCallbacks(handler);

        BLEService* service = server->createService(SERVICE_UUID);
        cpm = create_ble_characteristic(
            service,
            CPM_CHAR_UUID,
            CPM_DEC_UUID,
            "counts per minute"
        );
        msvh = create_ble_characteristic(
            service,
            MSV_CHAR_UUID,
            MSV_DESC_UUID,
            "microsievert per hour"
        );

        service->start();

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
        msvh = nullptr;
        handler = nullptr;
        active = false;
        Serial.println("BluetoothServer stopped");
    }
}

bool BluetoothServer::is_active() {
    return active;
}

void BluetoothServer::send_data(float msvh_val, int cpm_val) {
    if(active) {
        if(handler->isConnected()) {
            char msvh_buf[16];
            snprintf(msvh_buf, sizeof(msvh_buf), "%f", msvh_val);
            msvh->setValue(msvh_buf);
            char cpm_buf[16];
            ltoa(cpm_val, cpm_buf, 10);
            cpm->setValue(cpm_buf);
            msvh->notify();
            cpm->notify();
        }
    }
}

BLECharacteristic* BluetoothServer::create_ble_characteristic(BLEService* service, char* char_uuid, char* desc_uuid, char* name, int start)
{
    BLECharacteristic* characteristic = new BLECharacteristic(
        char_uuid,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_NOTIFY
    );
    BLEDescriptor* descriptor = new BLEDescriptor(desc_uuid);

    service->addCharacteristic(characteristic);
    char buf[16];
    ltoa(start, buf, 10);
    characteristic->setValue(buf);
    characteristic->addDescriptor(descriptor);
    characteristic->addDescriptor(new BLE2902());
    descriptor->setValue(name);

    return characteristic;
}