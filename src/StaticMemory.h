#ifndef GEIGERCOUNTER_STATICMEMORY_H
#define GEIGERCOUNTER_STATICMEMORY_H

#include <Arduino.h>
#include <EEPROM.h>

#define REGISTER_SIZE 32

enum MemoryRegister {
    DEFINED = 0,
    SSID = 1,
    PASSWORD = 33,
    API_ENDPOINT = 65,
    API_USER = 97,
    API_TOKEN = 129
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
    static void define();
    static void undefine();
    static bool is_defined();

    static bool write(MemoryRegister reg, String data);
    static char* read(MemoryRegister reg);
    static bool save();
    static void clear(int max);

};

#endif