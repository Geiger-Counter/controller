#include "Settings.h"

struct Settings* load_settings() {
    char* ssid = StaticMemory::read(MemoryRegister::SSID);
    char* password = StaticMemory::read(MemoryRegister::PASSWORD);
    char* username = StaticMemory::read(MemoryRegister::API_USER);
    char* token = StaticMemory::read(MemoryRegister::API_TOKEN);
    char* endpoint = StaticMemory::read(MemoryRegister::API_ENDPOINT);

    struct APISettings* api = malloc(sizeof(APISettings));
    struct Settings* settings = malloc(sizeof(Settings));

    api->username = username;
    api->token = token;
    api->endpoint_uri = endpoint;

    settings->ssid = ssid;
    settings->password = password;
    settings->auditive_counter = false;
    settings->api = api;

    return settings;
}

bool save_settings(struct Settings* settings) {

    struct APISettings* api = settings->api;
    StaticMemory::write(MemoryRegister::SSID, settings->ssid);
    StaticMemory::write(MemoryRegister::PASSWORD, settings->password);
    StaticMemory::write(MemoryRegister::AUDITIVE_COUNTER, settings->auditive_counter);
    StaticMemory::write(MemoryRegister::API_USER, api->username);
    StaticMemory::write(MemoryRegister::API_TOKEN, api->token);
    StaticMemory::write(MemoryRegister::API_ENDPOINT, api->endpoint_uri);

    return true;

}
