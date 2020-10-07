#include "CharacteristicCallbackHandler.h"

CharacteristicCallbackHandler::CharacteristicCallbackHandler(Settings* _settings) {
    settings = _settings;
}

CharacteristicCallbackHandler::~CharacteristicCallbackHandler() {}

void CharacteristicCallbackHandler::onWrite(BLECharacteristic* characteristic) {
    const char* uuid = characteristic->getUUID().toString().c_str();
    std::string value = characteristic->getValue();
    if(uuid == SETTINGS_SSID_CHAR_UUID) {
        settings->ssid = value.c_str();
    } else if (uuid == SETTINGS_PASSWORD_CHAR_UUID) {
        settings->password = value.c_str();
    } else if (uuid == SETTINGS_ENDPOINT_CHAR_UUID) {
        settings->api->endpoint_uri = value.c_str();
    } else if (uuid == SETTINGS_USERNAME_CHAR_UUID) {
        settings->api->username = value.c_str();
    } else if (uuid == SETTINGS_TOKEN_CHAR_UUID) {
        settings->api->token = value.c_str();
    }

    save_settings(settings);
}