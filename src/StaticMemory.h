#ifndef GEIGERCOUNTER_STATICMEMORY_H
#define GEIGERCOUNTER_STATICMEMORY_H

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

/**
 * @brief 
 * 
 */
class StaticMemory 
{

public:

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    static bool setup();

    static bool write(MemoryRegister reg, String data);
    static char* read(MemoryRegister reg);
    static bool save();
    static void clear(MemoryRegister reg);

};

#endif