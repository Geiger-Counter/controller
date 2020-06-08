#include "CharacteristicCallbackHandler.h"

CharacteristicCallbackHandler::CharacteristicCallbackHandler(struct Settings* settings) {
    settings = settings;
}

CharacteristicCallbackHandler::~CharacteristicCallbackHandler() {}

void CharacteristicCallbackHandler::onWrite(BLECharacteristic* characteristic) {
    Serial.println("OnWrite Event");
    const char* uuid = characteristic->getUUID().toString().c_str();
    std::string value = characteristic->getValue();
    if(uuid == SETTINGS_SSID_CHAR_UUID) {
        settings->ssid = value.c_str();
    } else if(uuid == SETTINGS_PASSWORD_CHAR_UUID) {
        settings->password = value.c_str();
    }
}