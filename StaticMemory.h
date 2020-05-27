#ifndef STATICMEMORY_H
#define STATICMEMORY_H

#include <Arduino.h>
#include <EEPROM.h>

#define REGISTER_SIZE 32

enum MemoryRegister {
    SSID = 0,
    PASSWORD = 32,
    API_ENDPOINT = 64,
    API_USER = 96,
    API_TOKEN = 128,
    AUDITIVE_COUNTER = 164
};

class StaticMemory 
{

public:

    static bool setup();

    static bool write(MemoryRegister register, String data);
    static char* read(MemoryRegister register);
    static bool save();
    static void clear(MemoryRegister register);

};

#endif