#include "BluetoothServer.h"

BluetoothServer::BluetoothServer(Settings* _settings, bool start) {

    settings = _settings;
    active = false;

    if(start) {
        BluetoothServer::start();
    }

}

void BluetoothServer::start() {
    if(!active) {
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
        data_service->start();
        settings_service->start();
        BLEAdvertising* advertising = BLEDevice::getAdvertising();
        advertising->addServiceUUID(DATA_SERVICE_UUID);
        advertising->setScanResponse(true);
        advertising->setMinPreferred(0x06);
        advertising->setMinPreferred(0x12);
        BLEDevice::startAdvertising();
        Serial.println("BluetoothServer running");
        active = true;
    }
    Serial.println("End");
}

void BluetoothServer::stop() {
    if(active) {
        Serial.println("Stopping Bluetooth Server ...");
        BLEDevice::deinit();
        delete server;
        delete cpm;
        delete msvh;
        delete ssid;
        delete password;
        delete auditive;
        delete endpoint;
        delete username;
        delete token;
        delete serviceHandler;
        delete characteristicHandler;
        server = nullptr;
        cpm = nullptr;
        msvh = nullptr;
        ssid = nullptr;
        password = nullptr;
        auditive = nullptr;
        endpoint = nullptr;
        username = nullptr;
        token = nullptr;
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
    if(tmpl.write) {
        characteristic->setCallbacks(characteristicHandler);
    }
    return characteristic;
}

void BluetoothServer::build_characteristics(BLEService* data_service, BLEService* settings_service) {
    cpm = create_ble_characteristic({
        data_service,
        DATA_CPM_CHAR_UUID,
        DATA_CPM_DESC_UUID,
        "counts per minute",
        "-1",
        true,
        false,
        true
    });
    msvh = create_ble_characteristic({
        data_service,
        DATA_MSV_CHAR_UUID,
        DATA_MSV_DESC_UUID,
        "microsievert per hour",
        "-1",
        true,
        false,
        true
    });
    impulse = create_ble_characteristic({
        data_service,
        DATA_IMPULSE_CHAR_UUID,
        DATA_IMPULSE_DESC_UUID,
        "decay_impulse",
        "-1",
        true,
        false,
        true
    });
    username = create_ble_characteristic({
        settings_service,
        SETTINGS_USERNAME_CHAR_UUID,
        SETTINGS_USERNAME_DESC_UUID,
        "api endpoint username",
        settings->api->username,
        true,
        true,
        true
    });
    endpoint = create_ble_characteristic({
        settings_service,
        SETTINGS_ENDPOINT_CHAR_UUID,
        SETTINGS_ENDPOINT_DESC_UUID,
        "api endpoint uri",
        settings->api->endpoint_uri,
        true,
        true,
        true
    });
    token = create_ble_characteristic({
        settings_service,
        SETTINGS_TOKEN_CHAR_UUID,
        SETTINGS_TOKEN_DESC_UUID,
        "access token for api",
        "",
        false,
        true,
        true
    });
    ssid = create_ble_characteristic({
        settings_service,
        SETTINGS_SSID_CHAR_UUID,
        SETTINGS_SSID_DESC_UUID,
        "ssid for wifi connection",
        settings->ssid,
        true,
        true,
        true
    }); 
    password = create_ble_characteristic({
        settings_service,
        SETTINGS_PASSWORD_CHAR_UUID,
        SETTINGS_PASSWORD_DESC_UUID,
        "password for wifi connection",
        "",
        false,
        true,
        true
    });
}