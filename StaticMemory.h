#ifndef STATICMEMORY_H
#define STATICMEMORY_H

#include <Arduino.h>
#include <EEPROM.h>

#define REGISTER_SIZE 32

enum MemoryRegister {
    SSID = 0,
    PASSWORD = 32
};

class StaticMemory 
{

public:

    static bool setup();

    static bool write(MemoryRegister register, String data);
    static String read(MemoryRegister register);
    static bool save();
    static void clear(MemoryRegister register);

};

#endif