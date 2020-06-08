#include "BluetoothServer.h"

BluetoothServer::BluetoothServer(struct Settings* settings, bool start) {

    settings = settings;
    active = false;

    if(start) {
        BluetoothServer::start();
    }

}

void BluetoothServer::start() {

    if(!active) {
        active = true;
        Serial.print("BLE initialized: ");
        Serial.println(BLEDevice::getInitialized());
        BLEDevice::init("GeigerCounter BT Server");
        Serial.println("BluetoothServer starting...");
        server = BLEDevice::createServer();

        serviceHandler = new ServiceCallbackHandler();
        characteristicHandler = new CharacteristicCallbackHandler(settings);
        server->setCallbacks(serviceHandler);

        BLEService* data_service = server->createService(DATA_SERVICE_UUID);
        BLEService* settings_service = server->createService(SETTINGS_SERVICE_UUID);

        build_characteristics(data_service, settings_service);        
        ssid->setCallbacks(characteristicHandler);

        data_service->start();
        settings_service->start();

        BLEAdvertising* advertising = BLEDevice::getAdvertising();
        advertising->addServiceUUID(DATA_SERVICE_UUID);
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
        BLEDevice::deinit();
        delete server;
        delete cpm;
        delete msvh;
        delete serviceHandler;
        delete characteristicHandler;
        server = nullptr;
        cpm = nullptr;
        msvh = nullptr;
        serviceHandler = nullptr;
        characteristicHandler = nullptr;
        active = false;
        Serial.println("BluetoothServer stopped");
    }
}

bool BluetoothServer::is_active() {
    return active;
}

void BluetoothServer::send_data(float msvh_val, int cpm_val) {
    if(active) {
        if(serviceHandler->isConnected()) {
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

void BluetoothServer::decay_impulse(unsigned long timestamp) {
    if(active) {
        if(serviceHandler->isConnected()) {
            char buff[8];
            snprintf(buff, sizeof(buff), "%l", timestamp);
            impulse->setValue(buff);
            impulse->notify();
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

void BluetoothServer::build_characteristics(BLEService* data, BLEService* settings) {
    cpm = create_ble_characteristic(
            data,
            DATA_CPM_CHAR_UUID,
            DATA_CPM_DEC_UUID,
            "counts per minute"
        );
        msvh = create_ble_characteristic(
            data,
            DATA_MSV_CHAR_UUID,
            DATA_MSV_DESC_UUID,
            "microsievert per hour"
        );
        impulse = create_ble_characteristic(
            data,
            DATA_IMPULSE_CHAR_UUID,
            DATA_IMPULSE_DEC_UUID,
            "decay impulse"
        );
        auditive = create_ble_characteristic(
            settings,
            SETTINGS_AUDITITVE_CHAR_UUID,
            SETTINGS_AUDITIVE_DEC_UUID,
            "auditive"
        );
        username = create_ble_characteristic(
            settings,
            SETTINGS_USERNAME_CHAR_UUID,
            SETTINGS_USERNAME_DEC_UUID,
            "api endpoint username"
        );
        endpoint = create_ble_characteristic(
            settings,
            SETTINGS_ENDPOINT_CHAR_UUID,
            SETTINGS_ENDPOINT_DEC_UUID,
            "api endpoint uri"
        );
        token = create_ble_characteristic(
            settings,
            SETTINGS_TOKEN_CHAR_UUID,
            SETTINGS_TOKEN_DEC_UUID,
            "access token for api"
        );
        ssid = create_ble_characteristic(
            settings,
            SETTINGS_SSID_CHAR_UUID,
            SETTINGS_SSID_DEC_UUID,
            "ssid value for api"
        );
        password = create_ble_characteristic(
            settings,
            SETTINGS_PASSWORD_CHAR_UUID,
            SETTINGS_PASSWORD_DEC_UUID,
            "wifi password"
        );
}