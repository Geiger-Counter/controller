#include "BluetoothServer.h"

BluetoothServer::BluetoothServer() {
    BluetoothServer::start();
}

void BluetoothServer::start() {
    Serial.print("BLE initialized: ");
    Serial.println(BLEDevice::getInitialized());
    BLEDevice::init("GeigerCounter BT Server");
    Serial.println("BluetoothServer starting...");
    this->server = BLEDevice::createServer();

    this->serviceHandler = new ServiceCallbackHandler();
    this->server->setCallbacks(this->serviceHandler);

    BLEService* data_service = server->createService(DATA_SERVICE_UUID);
    build_characteristics(data_service);

    data_service->start();

    BLEAdvertising* advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(DATA_SERVICE_UUID);
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06);
    advertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("BluetoothServer running");
}

void BluetoothServer::send_data(float msvh_val, int cpm_val) {
    if(this->serviceHandler->isConnected()) {
        char msvh_buf[16];
        snprintf(msvh_buf, sizeof(msvh_buf), "%f", msvh_val);
        this->msvh->setValue(msvh_buf);
        char cpm_buf[16];
        ltoa(cpm_val, cpm_buf, 10);
        this->cpm->setValue(cpm_buf);
        this->msvh->notify();
        this->cpm->notify();
    }
}

void BluetoothServer::decay_impulse(unsigned long timestamp) {
    if(this->serviceHandler->isConnected()) {
        char buff[8];
        snprintf(buff, sizeof(buff), "%l", timestamp);
        this->impulse->setValue(buff);
        this->impulse->notify();
    }
}

BLECharacteristic* BluetoothServer::create_ble_characteristic(struct CharacteristicTemplate tmpl)
{
    uint32_t permissions = BLECharacteristic::PROPERTY_NOTIFY;
    if(tmpl.read) {
        permissions = permissions | BLECharacteristic::PROPERTY_READ;
    }
    if(tmpl.write) {
        permissions = permissions | BLECharacteristic::PROPERTY_WRITE;
    }
    BLECharacteristic* characteristic = new BLECharacteristic(
        tmpl.uuid,
        permissions
    );
    BLEDescriptor* descriptor = new BLEDescriptor(tmpl.desc_uuid);

    tmpl.service->addCharacteristic(characteristic);
    characteristic->setValue(tmpl.default_value);
    characteristic->addDescriptor(descriptor);
    characteristic->addDescriptor(new BLE2902());
    descriptor->setValue(tmpl.desc);

    return characteristic;
}

void BluetoothServer::build_characteristics(BLEService* data_service) {
    this->cpm = create_ble_characteristic({
        data_service,
        DATA_CPM_CHAR_UUID,
        DATA_CPM_DESC_UUID,
        "counts per minute",
        "-1",
        true,
        false,
        true
    });
    this->msvh = create_ble_characteristic({
        data_service,
        DATA_MSV_CHAR_UUID,
        DATA_MSV_DESC_UUID,
        "microsievert per hour",
        "-1",
        true,
        false,
        true
    });
    this->impulse = create_ble_characteristic({
        data_service,
        DATA_IMPULSE_CHAR_UUID,
        DATA_IMPULSE_DESC_UUID,
        "decay_impulse",
        "-1",
        true,
        false,
        true
    });
}