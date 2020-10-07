#include "Settings.h"

Settings* load_settings() {

    APISettings* api = new APISettings();
    Settings* settings = new Settings();

    const char* ssid = StaticMemory::read(MemoryRegister::SSID);
    const char* password = StaticMemory::read(MemoryRegister::PASSWORD);
    const char* username = StaticMemory::read(MemoryRegister::API_USER);
    const char* token = StaticMemory::read(MemoryRegister::API_TOKEN);
    const char* endpoint = StaticMemory::read(MemoryRegister::API_ENDPOINT);

    api->username = username;
    api->token = token;
    api->endpoint_uri = endpoint;

    settings->ssid = ssid;
    settings->password = password;
    settings->api = api;

    return settings;
}

bool save_settings(Settings* settings) {

    APISettings* api = settings->api;
    StaticMemory::write(MemoryRegister::SSID, settings->ssid);
    StaticMemory::write(MemoryRegister::PASSWORD, settings->password);
    StaticMemory::write(MemoryRegister::API_USER, api->username);
    StaticMemory::write(MemoryRegister::API_TOKEN, api->token);
    StaticMemory::write(MemoryRegister::API_ENDPOINT, api->endpoint_uri);

    return true;

}
